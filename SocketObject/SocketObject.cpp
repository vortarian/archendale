#include <iostream>
#include <SocketObject/SocketObject.h>
#include <errno.h>

using namespace std;

// TODO
//	Set the recieve to not block;
//
namespace archendale
{
	/////////////////////////
	//
	//	Static's
	//
	/////////////////////////

	Transmit SocketObject::transmit;

	SocketObject::SocketObject(unsigned int readBufferLength = 10000)
	{
		m_socket 	 = 0;
		m_readBuffer 	 = 0;
		m_readBufferSize = readBufferLength;
		m_readBuffer	 = new unsigned char[m_readBufferSize];
	} // SocketObject
	
	SocketObject::SocketObject(const SocketObject& rhs)
	{
		delete m_readBuffer;
		m_readBuffer 	 = 0;
		m_socket 	 = rhs.m_socket;
		m_sendDataBuffer = rhs.m_sendDataBuffer;
		m_readDataBuffer = rhs.m_readDataBuffer;
		m_readBufferSize = rhs.m_readBufferSize;
		m_readBuffer 	 = new unsigned char[m_readBufferSize];
	} // SocketObject

	SocketObject::~SocketObject()
	{
		if(m_sendDataBuffer.size() > 0) send();
		delete m_readBuffer;
	} // ~SocketObject

	///////////////////////////////
	//
	//	Buffer Access Functions
	//
	///////////////////////////////

	// writeToBuffer:
	//
	void SocketObject::writeToBuffer(const unsigned char* beg, const unsigned char* end)
	{
		while(beg != end)
                {
                        m_sendDataBuffer.push_back(*beg);
			beg++;
                } // for
	} // writeToBuffer

	// writeToBuffer:
	//
	inline void SocketObject::writeToBuffer(const char* beg, const char* end)
	{
		writeToBuffer((const unsigned char*) beg, (const unsigned char*) end);
	} // writeToBuffer

	// send:
	//
	void SocketObject::send()
	{
		if(m_sendDataBuffer.size() <= 0) return;
		unsigned char* data = 0;
		int sendSize = m_sendDataBuffer.size();
		data = new unsigned char[sendSize];
		if(data)
		{
			int i = 0;
			vector < unsigned char >::const_iterator beg = m_sendDataBuffer.begin();
			vector < unsigned char >::const_iterator end = m_sendDataBuffer.end();
			for(unsigned int i = 0; beg != end; i++)
			{	
				data[i] = *beg;
				beg++;	
			} // while
			m_sendDataBuffer.clear();

			int retValue = ::send(m_socket, data, sendSize, MSG_NOSIGNAL);
			// have sent the data, clear it so it doesn't send twice!
			if(-1 == retValue)
			{
				switch(errno)
				{
					case EBADF:
					{
						InvalidSocketDescriptorException exp;
						delete data;
						throw exp;
					}		
					break;
					case ENOTSOCK:
					{
						NotSocketDescriptorException exp;
						delete data;
						throw exp;
					}		
					break;
					case EFAULT:
					{
					}		
					break;
					case EMSGSIZE:
					{
						MessageToLargeException exp;
						delete data;
						throw exp;
					}		
					break;
					case EWOULDBLOCK:
					{
						OperationWillBlockException exp;
						delete data;
						throw exp;
					}		
					break;
					case ENOBUFS:
					{
						NetworkInterfaceOverflowException exp;
						delete data;
						throw exp;
					}		
					break;
					case EINTR:
					{
						SignalException exp;
						delete data;
						throw exp;
					}		
					break;
					case ENOMEM:
					{
						OutOfMemoryException exp;
						delete data;
						throw exp;
					}		
					break;
					case EINVAL:
					{
						InvalidArgumentException exp;
						delete data;
						throw exp;
					}		
					break;
					case EPIPE:
					{
						SocketClosedException exp;
						delete data;
						throw exp;
					}		
					break;
					default:
					{
						Exception exp("Faild to send in SocketObject");
						delete data;
						throw exp;
					}
				} // switch
			} // if(send . . .)
		} else {
			OutOfMemoryException exp("Failed to create send buffer in " __FILE__ ": send()");
			throw exp;
		} // if(data)
		delete data;
	} // send

	// get:
	//
	inline char SocketObject::get()
	{
		if(m_readDataBuffer.size() <= 0) recieve();
		char ret = m_readDataBuffer.front();
		m_readDataBuffer.pop();
		return ret;
	} // get

	// recieve:
	//
	void SocketObject::recieve()
	{
		int count = ::recv(m_socket, m_readBuffer, m_readBufferSize, MSG_NOSIGNAL );
		if(-1 == count)
		{
			switch(errno)
			{
				case EBADF:
				case ENOTSOCK:
				{
					InvalidSocketDescriptorException exp;
					throw exp;
				}		
				break;
				case ENOTCONN:
				{
					SocketNotConnectedException exp;
					throw exp;
				}		
				break;
				case EFAULT:
				{
					Exception exp("Data out of Address Bounds in recieve in: " __FILE__);
					throw exp;
				}		
				break;
				case EAGAIN:
				{
					OperationWillBlockException exp;
					throw exp;
				}		
				break;
				case EINTR:
				{
					SignalException exp;
					throw exp;
				}		
				break;
				case EINVAL:
				{
					InvalidArgumentException exp;
					throw exp;
				}		
				break;
				default:
				{
					Exception exp("Faild to read in SocketObject");
					throw exp;
				}
			} // switch
		} // if(recieve . . .)
		for(int i = 0; i < count; i++)
		{
			m_readDataBuffer.push(m_readBuffer[i]);
		} // count	
	} // recieve
	
	///////////////////////
	//
	//	Operators
	//
	///////////////////////	

	SocketObject& SocketObject::operator<<(const Transmit&)
	{
		send();
		return *this;		
	} //  operator>>(const Transmit&)

	SocketObject& SocketObject::operator<<(char data)
	{
		writeToBuffer(&data, &data + 1);
		return *this;
	} //  operator<<(char) data 

	SocketObject& SocketObject::operator>>(char& input)
	{
		input = get();
		return *this;
	} //  operator>>(char)

	SocketObject& SocketObject::operator<<(unsigned char data)
	{
		writeToBuffer(&data, &data + 1);
		return *this;
	} //  operator<<(unsigned char data)

	SocketObject& SocketObject::operator>>(unsigned char& input)
	{
		input = get();
		return *this;
	} //  operator>>(unsigned char)

	SocketObject& SocketObject::operator<<(const string& data)
	{
		const char* pData = data.c_str();
		int length = strlen(pData);
		writeToBuffer(data.begin(), pData + length + 1 );
		return *this;
	} //  operator<<(string)

	SocketObject& SocketObject::operator>>(string& input)
	{	
		char data = 0;
		while((data = get()) != '\0')
		{
			input += data;
		} // while
		return *this;
	} //  operator>>(string)

	SocketObject& SocketObject::operator<<(int data)
	{
		iConverter.m_data.value = data;
		writeToBuffer(iConverter.m_data.data, iConverter.m_data.data + iConverter.getSize());
		return *this;
	} //  operator<<(int) 

	SocketObject& SocketObject::operator>>(int& input)
	{
		for(int i = 0; i < iConverter.getSize(); i++)
		{
			iConverter.m_data.data[i] = get();
		} // for
		input = iConverter.m_data.value;
		return *this;
	} //  operator>>(int)

	SocketObject& SocketObject::operator<<(unsigned int data)
	{
		uiConverter.m_data.value = data;
		writeToBuffer(uiConverter.m_data.data, uiConverter.m_data.data + uiConverter.getSize());
		return *this;
	} //  operator<<(unsigned int data)

	SocketObject& SocketObject::operator>>(unsigned int& input)
	{
		for(int i = 0; i < uiConverter.getSize(); i++)
		{
			uiConverter.m_data.data[i] = get();
		} // for
		input = uiConverter.m_data.value;
		return *this;
	} //  operator>>(unsigned int)

	SocketObject& SocketObject::operator<<(double data)
	{
		dConverter.m_data.value = data;
		writeToBuffer(dConverter.m_data.data, dConverter.m_data.data + dConverter.getSize());
		return *this;
	} //  operator<<(double) data 

	SocketObject& SocketObject::operator>>(double& input)
	{
		for(int i = 0; i < dConverter.getSize(); i++)
		{
			dConverter.m_data.data[i] = get();
		} // for
		input = dConverter.m_data.value;
		return *this;
	} //  operator>>(double)

	SocketObject& SocketObject::operator<<(long data)
	{
		lConverter.m_data.value = data;
		writeToBuffer(lConverter.m_data.data, lConverter.m_data.data + lConverter.getSize());
		return *this;
	} //  operator<<(long) data 

	SocketObject& SocketObject::operator>>(long& input)
	{
		for(int i = 0; i < lConverter.getSize(); i++)
		{
			lConverter.m_data.data[i] = get();
		} // for
		input = lConverter.m_data.value;
		return *this;
	} //  operator>>(long)

	SocketObject& SocketObject::operator<<(unsigned long data)
	{
		ulConverter.m_data.value = data;
		writeToBuffer(ulConverter.m_data.data, ulConverter.m_data.data + ulConverter.getSize());
		return *this;
	} //  operator<<(unsigned long data)

	SocketObject& SocketObject::operator>>(unsigned long& input)
	{
		for(int i = 0; i < ulConverter.getSize(); i++)
		{
			ulConverter.m_data.data[i] = get();
		} // for
		input = ulConverter.m_data.value;
		return *this;
	} //  operator>>(unsigned long)

	SocketObject& SocketObject::operator<<(float data)
	{
		fConverter.m_data.value = data;
		writeToBuffer(fConverter.m_data.data, fConverter.m_data.data + fConverter.getSize());
		return *this;
	} //  operator<<(float data)

	SocketObject& SocketObject::operator>>(float& input)
	{
		for(int i = 0; i < fConverter.getSize(); i++)
		{
			fConverter.m_data.data[i] = get();
		} // for
		input = fConverter.m_data.value;
		return *this;
	} //  operator>>(float)

} // archendale

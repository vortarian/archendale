#include <iostream>
#include <SocketObject/SocketObject.h>
#include <errno.h>

using namespace std;

namespace archendale
{
	/////////////////////////
	//
	//	Static's
	//
	/////////////////////////

	Transmit SocketObject::transmit;

	SocketObject::SocketObject()
	{
		m_socket = 0;
	} // SocketObject
	
	SocketObject::SocketObject(const SocketObject& rhs)
	{
		m_socket = rhs.m_socket;
		m_dataBuffer = rhs.m_dataBuffer;
	} // SocketObject

	SocketObject::~SocketObject()
	{
		if(m_dataBuffer.size() > 0) send();
	} // ~SocketObject

	///////////////////////////////
	//
	//	Buffer Access Functions
	//
	///////////////////////////////

	// send:
	//
	void SocketObject::send()
	{
		if(m_dataBuffer.size() <= 0) return;
		unsigned char* data = 0;
		data = new unsigned char[m_dataBuffer.size()];
		if(data)
		{
			int i = 0;
			vector < unsigned char >::const_iterator beg = m_dataBuffer.begin();
			vector < unsigned char >::const_iterator end = m_dataBuffer.end();
			cerr << "data[0-" << end - beg << "]: { "; // For Debugging
			for(unsigned int i = 0; beg != end; i++)
			{	
				data[i] = *beg;
				beg++;
				cerr << (unsigned int)(data[i]) << "  "; // For Debugging
			} // while
			cerr << "}" << endl; // For Debugging

			// have the data, clear it so it doesn't send twice!
			m_dataBuffer.clear();
/*
			if(-1 == ::send(m_socket, data, m_dataBuffer.size(), MSG_NOSIGNAL))
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
*/
		} else {
			OutOfMemoryException exp("Failed to create send buffer in " __FILE__ ": send()");
			throw exp;
		} // if(data)
		delete data;
	};

	// writeToBuffer:
	void SocketObject::writeToBuffer(unsigned char* beg, unsigned char* end)
	{
		while(beg != end)
                {
                        m_dataBuffer.push_back(*beg);
			beg++;
                } // for
	} // writeToBuffer

	// writeToBuffer:
	inline void SocketObject::writeToBuffer(char* beg, char* end)
	{
		writeToBuffer((unsigned char*) beg, (unsigned char*) end);
	} // writeToBuffer
	
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

	SocketObject& SocketObject::operator>>(char)
	{
		return *this;
	} //  operator>>(char)

	SocketObject& SocketObject::operator<<(unsigned char data)
	{
		writeToBuffer(&data, &data + 1);
		return *this;
	} //  operator<<(unsigned char data)

	SocketObject& SocketObject::operator>>(unsigned char)
	{
		return *this;
	} //  operator>>(unsigned char)

	SocketObject& SocketObject::operator<<(char* data)
	{
		int len = strlen(data);
		writeToBuffer(data, data + len + 1);
		return *this;
	} //  operator<<(char* data)

	SocketObject& SocketObject::operator>>(char*)
	{
		return *this;
	} //  operator>>(char*)

	SocketObject& SocketObject::operator<<(unsigned char* data)
	{
		int len = strlen((char *)data);
		writeToBuffer(data, data + len + 1);
		return *this;
	} //  operator<<(unsigned char*) data 

	SocketObject& SocketObject::operator>>(unsigned char*)
	{
		return *this;
	} //  operator>>(unsigned char*) 

	SocketObject& SocketObject::operator<<(int data)
	{
		iConverter.m_data.value = data;
		writeToBuffer(iConverter.m_data.data, iConverter.m_data.data + iConverter.getSize());
		return *this;
	} //  operator<<(int) 

	SocketObject& SocketObject::operator>>(int)
	{
		return *this;
	} //  operator>>(int)

	SocketObject& SocketObject::operator<<(unsigned int data)
	{
		uiConverter.m_data.value = data;
		writeToBuffer(uiConverter.m_data.data, uiConverter.m_data.data + uiConverter.getSize());
		return *this;
	} //  operator<<(unsigned int data)

	SocketObject& SocketObject::operator>>(unsigned int)
	{
		return *this;
	} //  operator>>(unsigned int)

	SocketObject& SocketObject::operator<<(double data)
	{
		dConverter.m_data.value = data;
		writeToBuffer(dConverter.m_data.data, dConverter.m_data.data + dConverter.getSize());
		return *this;
	} //  operator<<(double) data 

	SocketObject& SocketObject::operator>>(double)
	{
		return *this;
	} //  operator>>(double)

	SocketObject& SocketObject::operator<<(long data)
	{
		lConverter.m_data.value = data;
		writeToBuffer(lConverter.m_data.data, lConverter.m_data.data + lConverter.getSize());
		return *this;
	} //  operator<<(long) data 

	SocketObject& SocketObject::operator>>(long)
	{
		return *this;
	} //  operator>>(long)

	SocketObject& SocketObject::operator<<(unsigned long data)
	{
		ulConverter.m_data.value = data;
		writeToBuffer(ulConverter.m_data.data, ulConverter.m_data.data + ulConverter.getSize());
		return *this;
	} //  operator<<(unsigned long data)

	SocketObject& SocketObject::operator>>(unsigned long)
	{
		return *this;
	} //  operator>>(unsigned long)

	SocketObject& SocketObject::operator<<(float data)
	{
		fConverter.m_data.value = data;
		writeToBuffer(fConverter.m_data.data, fConverter.m_data.data + fConverter.getSize());
		return *this;
	} //  operator<<(float data)

	SocketObject& SocketObject::operator>>(float)
	{
		return *this;
	} //  operator>>(float)

} // archendale

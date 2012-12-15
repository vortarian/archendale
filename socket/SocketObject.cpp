#include <iostream>
#include <socket/SocketObject.h>
#include <unistd.h>
#include <typeinfo>
#include <errno.h>
#include <cstring>

using namespace std;

// TODO
//	Set the receive to not block;
//
namespace archendale
{
	/////////////////////////
	//
	//	Static's
	//
	/////////////////////////

	Transmit Socket::transmit;

	/////////////////////////
	//
	//	Class
	//
	/////////////////////////

	Socket::Socket(unsigned int readBufferLength)
	{
		m_readBuffer 	 = 0;
		m_readBufferSize = readBufferLength;
		m_readBuffer	 = new char[m_readBufferSize];
	} // SocketObject

	// This is a private member, as it is bad to share a handle	
	Socket::Socket(const Socket& rhs)
	{
		m_readBuffer 	 = 0;
		m_socketHandle 	 = rhs.m_socketHandle;
		m_sendDataBuffer = rhs.m_sendDataBuffer;
		m_readDataBuffer = rhs.m_readDataBuffer;
		m_readBufferSize = rhs.m_readBufferSize;
		m_readBuffer 	 = new char[m_readBufferSize];
	} // SocketObject

	Socket::~Socket()
	{
		// Send remaining Data if possible
		try 
		{
			if(m_sendDataBuffer.size() > 0) send();
		} catch (Exception& exp)
		{
			// Catch any exceptions, report and swallow them
			std::cerr << "Unknown Exception caught: " << endl
				<< "type: " << typeid(exp).name() << endl
				<< "why: " << exp.why() << endl;
		} // try
		delete m_readBuffer;
	} // ~SocketObject

	// This is a private member, as it is bad to share a handle	
	const Socket& Socket::operator=(const Socket& rhs)
	{
		delete m_readBuffer;
		m_readBuffer 	 = 0;
		m_socketHandle 	 = rhs.m_socketHandle;
		m_sendDataBuffer = rhs.m_sendDataBuffer;
		m_readDataBuffer = rhs.m_readDataBuffer;
		m_readBufferSize = rhs.m_readBufferSize;
		m_readBuffer 	 = new char[m_readBufferSize];
		return *this;
	} // operator=

	///////////////////////////////
	//
	//	Buffer Access Functions
	//
	///////////////////////////////

	// send:
	//
	void Socket::send()
	{
		if(m_sendDataBuffer.size() <= 0) return;
		int retValue = 0;
		while(m_sendDataBuffer.size() > 0 && retValue >= 0)
		{
			retValue = ::send(m_socketHandle->getSocket(), m_sendDataBuffer.c_str(), m_sendDataBuffer.size(), MSG_NOSIGNAL);
			m_socketHandle->incrementBytesSent(retValue);
			// have sent the data, clear it so it doesn't send twice!
			if(retValue >= 0) m_sendDataBuffer.erase(0, retValue);
		} // while
		if(-1 == retValue)
		{
			switch(errno)
			{
				case EBADF:
				{
					InvalidDescriptorException exp(__FILE__);
					throw exp;
				}		
				break;
				case ENOTSOCK:
				{
					NotDescriptorException exp(__FILE__);
					throw exp;
				}		
				break;
				case EFAULT:
				{
				}		
				break;
				case EMSGSIZE:
				{
					MessageToLargeException exp(__FILE__);
					throw exp;
				}		
				break;
				case EWOULDBLOCK:
				{
					OperationWillBlockException exp(__FILE__);
					throw exp;
				}		
				break;
				case ENOBUFS:
				{
					NetworkInterfaceOverflowException exp(__FILE__);
					throw exp;
				}		
				break;
				case EINTR:
				{
					SignalException exp(__FILE__);
					throw exp;
				}		
				break;
				case ENOMEM:
				{
					OutOfMemoryException exp(__FILE__);
					throw exp;
				}		
				break;
				case EINVAL:
				{
					InvalidArgumentException exp(__FILE__);
					throw exp;
				}		
				break;
				case EPIPE:
				{
					ClosedException exp(__FILE__);
					throw exp;
				}		
				break;
				default:
				{
					SocketException exp("Failed to send in SocketObject");
					throw exp;
				}
			} // switch
		} // if(-1 . . .
	} // send

	// receive:
	//
	void Socket::receive()
	{
		int count = ::recv(m_socketHandle->getSocket(), m_readBuffer, m_readBufferSize, MSG_NOSIGNAL);
		if(count >= 0 )
		{
			m_socketHandle->incrementBytesReceived(count);
			m_readDataBuffer.append(m_readBuffer, count);
		} else
		{
			switch(errno)
			{
				case EBADF:
				case ENOTSOCK:
				{
					InvalidDescriptorException exp(__FILE__);
					throw exp;
				}		
				break;
				case ENOTCONN:
				{
					NotConnectedException exp(__FILE__);
					throw exp;
				}		
				break;
				case EFAULT:
				{
					Exception exp("Data out of Address Bounds in receive in: " __FILE__);
					throw exp;
				}		
				break;
				case EAGAIN:
				{
					OperationWillBlockException exp(__FILE__);
					throw exp;
				}		
				break;
				case EINTR:
				{
					SignalException exp(__FILE__);
					throw exp;
				}		
				break;
				case EINVAL:
				{
					InvalidArgumentException exp(__FILE__);
					throw exp;
				}		
				break;
				default:
				{
					SocketException exp("Failed to read in SocketObject");
					throw exp;
				}
			} // switch
		} // if(-1 != ...
	} // receive
	
	///////////////////////
	//
	//	Operators
	//
	///////////////////////	

	Socket& Socket::operator<<(const Transmit&)
	{
		send();
		return *this;		
	} //  operator>>(const Transmit&)

	Socket& Socket::operator<<(char data)
	{
		m_sendDataBuffer += data;
		return *this;
	} //  operator<<(char) data 

	Socket& Socket::operator>>(char& input)
	{
		input = get();
		return *this;
	} //  operator>>(char)

	Socket& Socket::operator<<(unsigned char data)
	{
		m_sendDataBuffer += char(data);
		return *this;
	} //  operator<<(unsigned char data)

	Socket& Socket::operator>>(unsigned char& input)
	{
		input = get();
		return *this;
	} //  operator>>(unsigned char)

	Socket& Socket::operator<<(const string& data)
	{
		m_sendDataBuffer += data;
		return *this;
	} //  operator<<(string)

	Socket& Socket::operator>>(string& input)
	{	
		getline(input);
		return *this;
	} //  operator>>(string)

	Socket& Socket::operator<<(int data)
	{
		iConverter.m_data.value = data;
		m_sendDataBuffer.append(iConverter.m_data.data, iConverter.getSize());
		return *this;
	} //  operator<<(int) 

	Socket& Socket::operator>>(int& input)
	{
		for(int i = 0; i < iConverter.getSize(); i++)
		{
			iConverter.m_data.data[i] = get();
		} // for
		input = iConverter.m_data.value;
		return *this;
	} //  operator>>(int)

	Socket& Socket::operator<<(unsigned int data)
	{
		uiConverter.m_data.value = data;
		m_sendDataBuffer.append(uiConverter.m_data.data, uiConverter.getSize());
		return *this;
	} //  operator<<(unsigned int data)

	Socket& Socket::operator>>(unsigned int& input)
	{
		for(int i = 0; i < uiConverter.getSize(); i++)
		{
			uiConverter.m_data.data[i] = get();
		} // for
		input = uiConverter.m_data.value;
		return *this;
	} //  operator>>(unsigned int)

	Socket& Socket::operator<<(double data)
	{
		dConverter.m_data.value = data;
		m_sendDataBuffer.append(dConverter.m_data.data, dConverter.getSize());
		return *this;
	} //  operator<<(double) data 

	Socket& Socket::operator>>(double& input)
	{
		for(int i = 0; i < dConverter.getSize(); i++)
		{
			dConverter.m_data.data[i] = get();
		} // for
		input = dConverter.m_data.value;
		return *this;
	} //  operator>>(double)

	Socket& Socket::operator<<(long data)
	{
		lConverter.m_data.value = data;
		m_sendDataBuffer.append(lConverter.m_data.data, lConverter.getSize());
		return *this;
	} //  operator<<(long) data 

	Socket& Socket::operator>>(long& input)
	{
		for(int i = 0; i < lConverter.getSize(); i++)
		{
			lConverter.m_data.data[i] = get();
		} // for
		input = lConverter.m_data.value;
		return *this;
	} //  operator>>(long)

	Socket& Socket::operator<<(unsigned long data)
	{
		ulConverter.m_data.value = data;
		m_sendDataBuffer.append(ulConverter.m_data.data, ulConverter.getSize());
		return *this;
	} //  operator<<(unsigned long data)

	Socket& Socket::operator>>(unsigned long& input)
	{
		for(int i = 0; i < ulConverter.getSize(); i++)
		{
			ulConverter.m_data.data[i] = get();
		} // for
		input = ulConverter.m_data.value;
		return *this;
	} //  operator>>(unsigned long)

	Socket& Socket::operator<<(float data)
	{
		fConverter.m_data.value = data;
		m_sendDataBuffer.append(fConverter.m_data.data, fConverter.getSize());
		return *this;
	} //  operator<<(float data)

	Socket& Socket::operator>>(float& input)
	{
		for(int i = 0; i < fConverter.getSize(); i++)
		{
			fConverter.m_data.data[i] = get();
		} // for
		input = fConverter.m_data.value;
		return *this;
	} //  operator>>(float)

	int Socket::getSocket()
	{
		return m_socketHandle->getSocket();
	} // getSocket

	void Socket::setSocket(int socket)
	{	
		m_socketHandle->setSocket(socket);
	} // setSocket

	/////////////////////////
	//
	//	Static's
	//
	/////////////////////////

        // getline:
        //      Takes a SocketObject to read from,
        //      pointer to the data buffer to fill,
        //      size of the buffer,
        //      and a char delimiter to stop reading at
	//	leaves the delimiter in the socket stream
        void Socket::getline(char* buffer, unsigned int length, char delim)
	{
		if(m_readDataBuffer.size() <= 0) receive();
		unsigned int i = 0;
		// Read until we find that delimiter
		do
		{
			i = m_readDataBuffer.find(delim);
			if(i == string::npos) receive();
		} while(i == string::npos);
		unsigned int copyLength = i;
		if(copyLength > length) copyLength = length;
		strncpy(buffer, m_readDataBuffer.c_str(), copyLength);
		m_readDataBuffer.erase(0, copyLength);
	} // getline

        // getline:
        //      Takes a SocketObject to read from,
        //      pointer to the data buffer to fill,
        //      size of the buffer
        //      Reads until it finds whitespace
	//	leaves the delimiter in the socket stream
        void Socket::getline(char* buffer, unsigned int length)
	{
		if(m_readDataBuffer.size() <= 0) receive();
		unsigned int i = 0;
		// Read until we find that delimiter
		string::const_iterator beg = m_readDataBuffer.begin();
		string::const_iterator end = m_readDataBuffer.end();
		do
		{
			beg = m_readDataBuffer.begin() + i;
			end = m_readDataBuffer.end();
			while(beg != end)
			{
				if(isspace(*beg))
				{
					break;
				} // if
				i++;
				beg++;
			} // while
			if(beg == end) receive();
			// can not use end in the next statement,
			// as receive changes it, have to make new function 
			// call
		} while(beg != m_readDataBuffer.end());
		unsigned int copyLength = i;
		if(copyLength > length) copyLength = length;
		strncpy(buffer, m_readDataBuffer.c_str(), copyLength);
		m_readDataBuffer.erase(0, copyLength);
	} // getline

        // getline:     
        //      Takes a SocketObject to read from, 
        //      reference to the string to append to
        //      delimiter to stop reading at
        //      Reads until it finds the delimiter, 
	//	delimiter is removed from the string
        void Socket::getline(string& input, char delim)
	{
		if(m_readDataBuffer.size() <= 0) receive();
		string::size_type i = 0;
		// Read until we find that delimiter
		do
		{
			i = m_readDataBuffer.find(delim);
			if(i == string::npos) receive();
		} while(i == string::npos);
                input = m_readDataBuffer.substr(0, i);
                m_readDataBuffer.erase(0, i + 1);
	} // getline

        // getline:
        //      Takes a SocketObject to read from,
        //      reference to the string to append to
        //      delimiter to stop reading at
        //      Reads until it finds whitespace, removes
	//	final piece of whitespace
        void Socket::getline(string& input)
	{
		if(m_readDataBuffer.size() <= 0) receive();
		string::size_type i = 0;
		// Read until we find whitespace
		string::const_iterator beg = m_readDataBuffer.begin();
		string::const_iterator end = m_readDataBuffer.end();
		do
		{
			beg = m_readDataBuffer.begin() + i;
			end = m_readDataBuffer.end();
			while(beg != end)
			{
				if(isspace(*beg))
				{
					break;
				} // if
				i++;
				beg++;
			} // while
			if(beg == end) receive();
			// can not use end in the next statement,
			// as receive changes it, have to make new function 
			// call
		} while(beg != m_readDataBuffer.end());
		input = m_readDataBuffer.substr(0, i);
		m_readDataBuffer.erase(0, i + 1);
	} // getline

} // archendale

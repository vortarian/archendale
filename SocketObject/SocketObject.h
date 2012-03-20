
#ifndef SOCKETOBJECT_H
#define SOCKETOBJECT_H

#include <sys/types.h>
#include <sys/socket.h>    
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <SocketObject/SocketException.h>
#include <SocketObject/SocketHandle.h>
#include <ThreadObject/Mutex.h>
#include <Util/ReferenceCounter.h>

using std::vector;
using std::queue;
using std::string;

namespace archendale 
{
	// SocketDataConverter:
	//      Implementation Specific object
	//      used to convert < 1 byte simple atomic's to char
	//      without loss of precision
	template<class T> class SocketDataConverter
	{
	public:
		SocketDataConverter()
		{
			m_size = sizeof(T);
		} // SocketDataConverter

		~SocketDataConverter()
		{
		} // SocketDataConverter~

		unsigned int getSize();

		union
		{
			// convert up to 128 bit value . . .
			char data[16];
			T value;
		} m_data;
	private:
		unsigned int m_size;
	}; // SocketDataConverter 

	// Transmit Notifier:
	struct Transmit { };

	// SocketObject:
	//	PRE: Clients acquire before use, and release after, if in a MT environment	
	//	Each SocketObject keeps it's own copy of data buffers,
	//		e.g. if you have data in the buffer, and get a copy (assign)
	//		you will now have two copies of the buffer, one in each class
	class SocketObject : public Mutex
	{
	public:
		SocketObject(unsigned int = 10000);
		virtual ~SocketObject();

		// send:
		//	transmit the data
		void send();

		// receive:
		//	receive the data, read into buffer
		void receive();

		// get
		//	Return the first character from the read queue
		//		remove the character from the queue
		char get();
	
		// get
		//	Special function for reading a string, the string
		//	will be filled until a null terminator is found e.g. '\0'
		void get(string&);

		// writeToBuffer:
		//	write raw data to a buffer
		//	writeToBuffer(iterator start, iterator end);
		void writeToBuffer(const unsigned char*, const unsigned char*);
		void writeToBuffer(const char* beg, const char* end); // defers to unsigned version

		SocketObject& operator<<(char); 
		SocketObject& operator>>(char&); 
		SocketObject& operator<<(unsigned char); 
		SocketObject& operator>>(unsigned char&); 

		SocketObject& operator<<(const string&); 
		SocketObject& operator>>(string&); 

		SocketObject& operator<<(int); 
		SocketObject& operator>>(int&); 
		SocketObject& operator<<(unsigned int); 
		SocketObject& operator>>(unsigned int&); 

		SocketObject& operator<<(double); 
		SocketObject& operator>>(double&); 

		SocketObject& operator<<(long); 
		SocketObject& operator>>(long&); 
		SocketObject& operator<<(unsigned long); 
		SocketObject& operator>>(unsigned long&); 

		SocketObject& operator<<(float); 
		SocketObject& operator>>(float&); 
		
		static Transmit transmit;
		SocketObject& operator<<(const Transmit&); 

		// getline functionality

		// getline:	
		//	Takes a SocketObject to read from, 
		//	pointer to the data buffer to fill,
		//	size of the buffer,
		//	and a char delimiter to stop reading at
		void getline(char*, unsigned int, char);

		// getline:	
		//	Takes a SocketObject to read from, 
		//	pointer to the data buffer to fill,
		//	size of the buffer
		//	Reads until it finds whitespace
		void getline(char*, unsigned int);

		// getline:	
		//	Takes a SocketObject to read from, 
		//	reference to the string to append to
		//	delimiter to stop reading at
		//	Reads until it finds the delimiter
		void getline(std::string&, char);

		// getline:	
		//	Takes a SocketObject to read from, 
		//	reference to the string to append to
		//	delimiter to stop reading at
		//	Reads until it finds whitespace
		void getline(std::string&);

		// getBytesSent:
		//
		unsigned int getBytesSent() { return m_socketHandle->getBytesSent(); }

		// getBytesReceived:
		//
		unsigned int getBytesReceived() { return m_socketHandle->getBytesReceived(); }
	protected:
		// getSocket:
		//	Only usable by subclasses
		int getSocket();
		
		// setSocket:
		//	Only usable by subclasses
		void setSocket(int);

		// Can't have people sharing SocketHandles
		SocketObject(const SocketObject&);
		const SocketObject& operator=(const SocketObject&);
	private:

		string m_sendDataBuffer;
		string m_readDataBuffer;
		
		unsigned int m_readBufferSize; // The size to use for the read buffer
		char *m_readBuffer; 	// The buffer which recv() will read into

		SocketDataConverter<int>                 iConverter;
		SocketDataConverter<unsigned int>        uiConverter;
		SocketDataConverter<long>                lConverter;
		SocketDataConverter<unsigned long>       ulConverter;
		SocketDataConverter<double>              dConverter;
		SocketDataConverter<float>               fConverter;

		ReferenceCounter<SocketHandle> m_socketHandle;
	}; // SocketObject

	// get:
	//
	inline char SocketObject::get()
	{
		if(m_readDataBuffer.size() <= 0) receive();
		char ret = m_readDataBuffer[0];
		m_readDataBuffer.erase(0, 1);
		return ret;
	} // get

	// get:
	//	special get function for strings saves the looping
	inline void SocketObject::get(string& input)
	{
		if(m_readDataBuffer.size() <= 0) receive();
		string::size_type i = 0;
		// Read until we find that terminator
		do
		{
			i = m_readDataBuffer.find('\0');
			if(i == string::npos) receive();
		} while(i == string::npos);
		input = m_readDataBuffer.substr(0, i);
		m_readDataBuffer.erase(0, i + 1);
	} // get


	// getSize:
	// return the size of the socket
	template <class T>
	inline unsigned int SocketDataConverter<T>::getSize()
	{
		return m_size;
	} // getSize
				
	// writeToBuffer:
	//
	inline void SocketObject::writeToBuffer(const char* beg, const char* end)
	{
		while(beg != end)
		{
			m_sendDataBuffer += *beg;
			beg++;
		} // for
	} // writeToBuffer

	// writeToBuffer:
	//
	inline void SocketObject::writeToBuffer(const unsigned char* beg, const unsigned char* end)
	{
		writeToBuffer((const char*) beg, (const char*) end);
	} // writeToBuffer

} // archendale

#endif // SOCKETOBJECT_H

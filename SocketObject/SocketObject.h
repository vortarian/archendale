
#ifndef SOCKETOBJECT_H
#define SOCKETOBJECT_H

#include <sys/types.h>
#include <sys/socket.h>    
#include <strstream>
#include <vector>
#include <queue>
#include <string>
#include <SocketObject/SocketException.h>

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

		inline unsigned int getSize()
		{
			return m_size;
		} // getSize

		union
		{
			// convert up to 128 bit value . . .
			unsigned char data[16];
			T value;
		} m_data;
	private:
		unsigned int m_size;
	}; //SocketDataConverter 

	// Transmit Notifier:
	struct Transmit { };

	class SocketObject 
	{
	public:
		SocketObject(unsigned int = 10000);
		SocketObject(const SocketObject&);
		virtual ~SocketObject();

		// send:
		//	transmit the data
		void send();

		// recieve:
		//	recieve the data, read into buffer
		void recieve();

		// get
		//	Return the first character from the read queue
		//		remove the character from the queue
		inline char get();
	
		// writeToBuffer:
		//	write raw data to a buffer
		//	writeToBuffer(iterator start, iterator end);
		void writeToBuffer(const unsigned char*, const unsigned char*);
		inline void writeToBuffer(const char* beg, const char* end); // defers to unsigned version

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

	protected:
		int m_socket; // The socket itself

	private:
		vector < unsigned char > m_sendDataBuffer;
		queue  < unsigned char > m_readDataBuffer;
		
		unsigned int m_readBufferSize; // The size to use for the read buffer
		unsigned char *m_readBuffer; 	// The buffer which recv() will read into

		SocketDataConverter<int>                 iConverter;
		SocketDataConverter<unsigned int>        uiConverter;
		SocketDataConverter<long>                lConverter;
		SocketDataConverter<unsigned long>       ulConverter;
		SocketDataConverter<double>              dConverter;
		SocketDataConverter<float>               fConverter;
	}; // SocketObject
} // archendale

#endif // SOCKETOBJECT_H

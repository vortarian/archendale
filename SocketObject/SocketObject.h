
#ifndef SOCKETOBJECT_H
#define SOCKETOBJECT_H

#include <sys/types.h>
#include <sys/socket.h>    
#include <strstream>
#include <vector>
#include <SocketObject/SocketException.h>

using std::vector;

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
		SocketObject();
		SocketObject(const SocketObject&);
		virtual ~SocketObject();

		// send:
		//	transmit the data
		void send();

		// writeToBuffer:
		//	write raw data to a buffer
		//	writeToBuffer(iterator start, iterator end);
		void writeToBuffer(unsigned char*, unsigned char*);
		inline void writeToBuffer(char* beg, char* end); // defers to unsigned version

		SocketObject& operator<<(char); 
		SocketObject& operator>>(char); 
		SocketObject& operator<<(unsigned char); 
		SocketObject& operator>>(unsigned char); 

		SocketObject& operator<<(char*); 
		SocketObject& operator>>(char*); 
		SocketObject& operator<<(unsigned char*); 
		SocketObject& operator>>(unsigned char*); 

		SocketObject& operator<<(int); 
		SocketObject& operator>>(int); 
		SocketObject& operator<<(unsigned int); 
		SocketObject& operator>>(unsigned int); 

		SocketObject& operator<<(double); 
		SocketObject& operator>>(double); 

		SocketObject& operator<<(long); 
		SocketObject& operator>>(long); 
		SocketObject& operator<<(unsigned long); 
		SocketObject& operator>>(unsigned long); 

		SocketObject& operator<<(float); 
		SocketObject& operator>>(float); 
		
		static Transmit transmit;
		SocketObject& operator<<(const Transmit&); 

	private:
		vector < unsigned char > m_dataBuffer;
		int m_socket;

		SocketDataConverter<int>                 iConverter;
		SocketDataConverter<unsigned int>        uiConverter;
		SocketDataConverter<long>                lConverter;
		SocketDataConverter<unsigned long>       ulConverter;
		SocketDataConverter<double>              dConverter;
		SocketDataConverter<float>               fConverter;
	}; // SocketObject
} // archendale

#endif // SOCKETOBJECT_H


#ifndef SocketException_h
#define SocketException_h

#include <Exception/Exception.h>

namespace archendale
{

	class UnknownHostException : public Exception
	{
	public:
		UnknownHostException() { ; }
		UnknownHostException(const String& msg) : Exception(msg) { ; }
	}; // UnknownHostException

	class RetryHostLookupException : public Exception
	{
	public:
		RetryHostLookupException() { ; }
		RetryHostLookupException(const String& msg) : Exception(msg) { ; }
	}; // RetryHostLookupException

	class HostWithNoAddressException : public Exception
	{
	public:
		HostWithNoAddressException() { ; }
		HostWithNoAddressException(const String& msg) : Exception(msg) { ; }
	}; // HostWithNoAddressException

	// InvalidSocketDescriptorException:
       	//	EBADF   An invalid descriptor was specified.
	class InvalidSocketDescriptorException : public Exception
	{
	public:
		InvalidSocketDescriptorException() { ; }
		InvalidSocketDescriptorException(const String& msg) : Exception(msg) { ; }
	}; // InvalidSocketDescriptorException

	// SocketNotConnectedException:
       	//	ENOTCONN The Socket is not connected
	class SocketNotConnectedException : public Exception
	{
	public:
		SocketNotConnectedException() { ; }
		SocketNotConnectedException(const String& msg) : Exception(msg) { ; }
	}; // InvalidSocketDescriptorException

	// NotSocketDescriptorException :
	//	ENOTSOCK
        //		The argument s is not a socket.
	class NotSocketDescriptorException : public Exception
	{
	public:
		NotSocketDescriptorException() { ; }
		NotSocketDescriptorException(const String& msg) : Exception(msg) { ; }
	}; // NotSocketDescriptorException

	// MessageToLargeException: 
	// 	EMSGSIZE
	//	       The socket requires that message be sent atomically, and the size of the mes-
	//	       sage to be sent made this impossible.
	class MessageToLargeException : public Exception
	{
	public:
		MessageToLargeException() { ; }
		MessageToLargeException(const String& msg) : Exception(msg) { ; }
	}; // MessageToLargeException

	// OperationWillBlockException:
	//	EAGAIN or EWOULDBLOCK
	//		The socket is marked non-blocking and the requested operation would block.
	class OperationWillBlockException : public Exception
	{
	public:
		OperationWillBlockException() { ; }
		OperationWillBlockException(const String& msg) : Exception(msg) { ; }
	}; // OperationWillBlockException

	// NetworkInterfaceOverflowException:
	// 	ENOBUFS The output queue for a network interface was full.  This generally  indicates
	// 		that  the  interface has stopped sending, but may be caused by transient con-
	// 		gestion.  (This cannot occur in Linux, packets are just silently dropped when
	// 		a device queue overflows.)
	class NetworkInterfaceOverflowException : public Exception
	{
	public:
		NetworkInterfaceOverflowException() { ; }
		NetworkInterfaceOverflowException(const String& msg) : Exception(msg) { ; }
	}; // NetworkInterfaceOverflowException

	// SignalException :
       	//	EINTR   A signal occurred.
	class SignalException : public Exception
	{
	public:
		SignalException() { ; }
		SignalException(const String& msg) : Exception(msg) { ; }
	}; // Exception

	// SocketClosedException :
        //	EPIPE   The  local  end  has been shut down on a connection oriented socket.  In this
        //       	case the process will also receive a SIGPIPE unless MSG_NOSIGNAL is set.
	class SocketClosedException : public Exception
	{
	public:
		SocketClosedException() { ; }
		SocketClosedException(const String& msg) : Exception(msg) { ; }
	}; // SocketClosedException

} // archendale

#endif // SocketException_h

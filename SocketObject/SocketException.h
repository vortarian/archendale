
#ifndef Exception_h
#define Exception_h

#include <Exception/Exception.h>

// TODO:
//	Would probably be an excellent idea to start putting namespaces for
//	each subfolder, could actually have name clashing for
//	exception names
namespace archendale
{
		// SocketException:
		// 	Base class exception to be used for segregating 
		//	exceptions of Socket type
		class SocketException : public Exception
		{
		public:
			SocketException() { ; }
			SocketException(const string& msg) : Exception(msg) { ; }
		}; // SocketException

		class UnknownHostException : public SocketException
		{
		public:
			UnknownHostException() { ; }
			UnknownHostException(const string& msg) : SocketException(msg) { ; }
		}; // UnknownHostException

		class RetryHostLookupException : public SocketException
		{
		public:
			RetryHostLookupException() { ; }
			RetryHostLookupException(const string& msg) : SocketException(msg) { ; }
		}; // RetryHostLookupException

		class HostWithNoAddressException : public SocketException
		{
		public:
			HostWithNoAddressException() { ; }
			HostWithNoAddressException(const string& msg) : SocketException(msg) { ; }
		}; // HostWithNoAddressException

		// InvalidDescriptorException:
		//	EBADF   An invalid descriptor was specified.
		class InvalidDescriptorException : public SocketException
		{
		public:
			InvalidDescriptorException() { ; }
			InvalidDescriptorException(const string& msg) : SocketException(msg) { ; }
		}; // InvalidDescriptorException

		// NotConnectedException:
		//	ENOTCONN The Socket is not connected
		class NotConnectedException : public SocketException
		{
		public:
			NotConnectedException() { ; }
			NotConnectedException(const string& msg) : SocketException(msg) { ; }
		}; // InvalidDescriptorException

		// NotDescriptorException :
		//	ENOTSOCK
		//		The argument s is not a socket.
		class NotDescriptorException : public SocketException
		{
		public:
			NotDescriptorException() { ; }
			NotDescriptorException(const string& msg) : SocketException(msg) { ; }
		}; // NotDescriptorException

		// MessageToLargeException: 
		// 	EMSGSIZE
		//	       The socket requires that message be sent atomically, and the size of the mes-
		//	       sage to be sent made this impossible.
		class MessageToLargeException : public SocketException
		{
		public:
			MessageToLargeException() { ; }
			MessageToLargeException(const string& msg) : SocketException(msg) { ; }
		}; // MessageToLargeException

		// OperationWillBlockException:
		//	EAGAIN or EWOULDBLOCK or EINPROGRESS
		//		The socket is marked non-blocking and the requested operation would block.
		class OperationWillBlockException : public SocketException
		{
		public:
			OperationWillBlockException() { ; }
			OperationWillBlockException(const string& msg) : SocketException(msg) { ; }
		}; // OperationWillBlockException

		// NetworkInterfaceOverflowException:
		// 	ENOBUFS The output queue for a network interface was full.  This generally  indicates
		// 		that  the  interface has stopped sending, but may be caused by transient con-
		// 		gestion.  (This cannot occur in Linux, packets are just silently dropped when
		// 		a device queue overflows.)
		class NetworkInterfaceOverflowException : public SocketException
		{
		public:
			NetworkInterfaceOverflowException() { ; }
			NetworkInterfaceOverflowException(const string& msg) : SocketException(msg) { ; }
		}; // NetworkInterfaceOverflowException

		// SignalException :
		//	EINTR   A signal occurred.
		class SignalException : public SocketException
		{
		public:
			SignalException() { ; }
			SignalException(const string& msg) : SocketException(msg) { ; }
		}; // Exception

		// ClosedException :
		//	EPIPE   The  local  end  has been shut down on a connection oriented socket.  In this
		//       	case the process will also receive a SIGPIPE unless MSG_NOSIGNAL is set.
		class ClosedException : public SocketException
		{
		public:
			ClosedException() { ; }
			ClosedException(const string& msg) : SocketException(msg) { ; }
		}; // ClosedException

		// FirewallDeniedConnectionException :
		//	EPERM   The Firewall is denying this connection
		//       	
		class FirewallDeniedConnectionException : public SocketException
		{
		public:
			FirewallDeniedConnectionException() { ; }
			FirewallDeniedConnectionException(const string& msg) : SocketException(msg) { ; }
		}; // FirewallDeniedConnectionException

		// ProtocolNotSupportedException :
		//	EPROTONOSUPPORT 
		//		The Protocol is not supported in the domain	
		//       	
		class ProtocolNotSupportedException : public SocketException
		{
		public:
			ProtocolNotSupportedException() { ; }
			ProtocolNotSupportedException(const string& msg) : SocketException(msg) { ; }
		}; // ProtocolNotSupportedException

		// BoundException :
		//	EINVAL
		//		The socket has already been bound	
		//       	
		class BoundException : public SocketException
		{
		public:
			BoundException() { ; }
			BoundException(const string& msg) : SocketException(msg) { ; }
		}; // BoundException

		// ConnectedException :
		//	EISCONN
		//		The socket has already been connected
		//       	
		class ConnectedException : public SocketException
		{
		public:
			ConnectedException() { ; }
			ConnectedException(const string& msg) : SocketException(msg) { ; }
		}; // ConnectedException

		// ConnectionRefusedException :
		//	ECONNREFUSED
		//		The socket connection has been refused
		//       	
		class ConnectionRefusedException : public SocketException
		{
		public:
			ConnectionRefusedException() { ; }
			ConnectionRefusedException(const string& msg) : SocketException(msg) { ; }
		}; // ConnectionRefusedException

		// TimeOutException :
		//	ETIMEDOUT
		//		The socket connection has timed out
		//       	
		class TimeOutException : public SocketException
		{
		public:
			TimeOutException() { ; }
			TimeOutException(const string& msg) : SocketException(msg) { ; }
		}; // TimeOutException

		// NetworkUnreachableException :
		//	ENETUNREACH
		//		The network requested is unreachable
		//       	
		class NetworkUnreachableException : public SocketException
		{
		public:
			NetworkUnreachableException() { ; }
			NetworkUnreachableException(const string& msg) : SocketException(msg) { ; }
		}; // NetworkUnreachableException

		// AddressInUseException :
		//	EADDRINUSE
		//		Address is already in use
		//       	
		class AddressInUseException : public SocketException
		{
		public:
			AddressInUseException() { ; }
			AddressInUseException(const string& msg) : SocketException(msg) { ; }
		}; // AddressInUseException

		// RetryException :
		//	EAGAIN
		//		Retry the connection, no ports available
		//       	
		class RetryException : public SocketException
		{
		public:
			RetryException() { ; }
			RetryException(const string& msg) : SocketException(msg) { ; }
		}; // RetryException

		// TypeNotSupportedException :
		//	EAFNOSUPPORT
		//		Socket type is not supported
		//       	
		class TypeNotSupportedException : public SocketException
		{
		public:
			TypeNotSupportedException() { ; }
			TypeNotSupportedException(const string& msg) : SocketException(msg) { ; }
		}; // TypeNotSupportedException

		// SystemDenyException :
		//      EACCES, EPERM
		//      The user tried to connect to a broadcast address 
		//	without having the socket broadcast flag  enabled  
		//	or  the  connection  request failed because of a 
		//	local firewall rule.  
		//       	
		class SystemDenyException : public SocketException
		{
		public:
			SystemDenyException() { ; }
			SystemDenyException(const string& msg) : SocketException(msg) { ; }
		}; // SystemDenyExceptionCCES, EPERM

} // archendale

#endif // Exception_h

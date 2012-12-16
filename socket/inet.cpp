
#include <socket/inet.h>
#include <socket/internet_address.h>
#include <socket/name_resolver.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>

using std::string;
                     
namespace archendale
{
	// TODO:
	//	Need to define exceptions
	// 	Need to have it use getprotoent instead of hard coding protocol into socket

	// INETSocket:
	//	Default constructor for use by SocketServer
	inet::inet() : m_protocolName("tcp")
	{
		m_port = 0;
	} // INETSocket

	// INETSocket:
	//
	inet::inet(const internet_address& addr, int port) : m_protocolName("tcp")
	{
		m_address = addr;
		m_port = port;
		// Get the protocol id from the system 
		// TODO: this is specific to BSD systems, find POSIX method
		protoent* protocol = getprotobyname(m_protocolName.c_str());
		if(protocol == 0)
		{
			// Either the file does not exist, or there is some other error
			string error = 
				__FILE__ 
				": INETSocket::INETSocket() : " 
				"Unable to get the protocol "; 
			error += m_protocolName;
			Exception exp(error);
			throw exp;
		} // if	
		setSocket(socket(m_address.getType(), SOCK_STREAM, protocol->p_proto));
		if(-1 == getSocket())
		{
			switch(errno)
			{
                                case EPROTONOSUPPORT:
                                        {
                                                ProtocolNotSupportedException exp(__FILE__ ": INETSocket::INETSocket()");
                                                throw exp;
                                        }
                                        break;
                                case ENFILE:
                                        {
                                                OutOfMemoryException exp("Kernel Memory Exhausted : " __FILE__ ": INETSocket::INETSocket()");
                                                throw exp;
                                        }
                                        break;
                                case EMFILE:
                                        {
                                                SocketException exp("Process File Table Overflow in : " __FILE__ ": INETSocket::INETSocket()");
                                                throw exp;
                                        }
                                        break;
                                case EACCES:
                                        {
                                                AccessDeniedException exp(__FILE__ ": INETSocket::INETSocket()" ":");
                                                throw exp;
                                        }
                                        break;
                                case ENOMEM:
                                        {
                                                OutOfMemoryException exp(__FILE__ ": INETSocket::INETSocket()");
                                                throw exp;
                                        }
                                        break;
                                case EINVAL:
                                        {
                                                InvalidArgumentException exp(__FILE__ ": INETSocket::INETSocket()");
                                                throw exp;
                                        }
                                        break;
                                default:
                                        {
                                                SocketException exp(__FILE__ ": INETSocket::INETSocket()");
                                                throw exp;
                                        }
                        } // switch
		} // if 
	} // INETSocket

	// INETSocket:
	//
	inet::inet(const inet& in) : socket(in), m_protocolName("tcp")
	{
		m_address = in.m_address;
		m_port = in.m_port;
	} // INETSocket

	// INETSocket:
	//
	const inet& inet::operator=(const inet& in) 
	{
		socket::operator=(in);
		m_address = in.m_address;
		m_port = in.m_port;
	} // INETSocket

	// ~INETSocket:
	//
	inet::~inet()
	{
	} // ~INETSocket

	// connect:
	//	Connects the current socket
	void inet::connect()
	{
		sockaddr_in socketAttribute;
		socketAttribute.sin_family = m_address.getType();
		socketAttribute.sin_port  = htons(m_port);
		inet_aton(m_address.getAddress().c_str(), &socketAttribute.sin_addr);
		if(::connect(getSocket(), (sockaddr*) &socketAttribute, sizeof(socketAttribute)))
		{	
			switch(errno)
			{
				case EBADF:
					{
						InvalidDescriptorException exp(__FILE__ ": INETSocket::connect()");
						throw exp;
					}
					break;
				case ENOTSOCK:
					{
						NotDescriptorException exp(__FILE__ ": INETSocket::connect()");
						throw exp;
					}
					break;
				case EISCONN:
					{
						ConnectedException exp(__FILE__ ": INETSocket::connect()");
						throw exp;
					}
					break;
				case ECONNREFUSED:
					{
						ConnectionRefusedException exp(__FILE__ ": INETSocket::connect()");
						throw exp;
					}
					break;
				case ETIMEDOUT:
					{
						TimeOutException exp(__FILE__ ": INETSocket::connect()");
						throw exp;
					}
					break;
				case ENETUNREACH:
					{
						NetworkUnreachableException exp(__FILE__ ": INETSocket::connect()");
						throw exp;
					}
					break;
				case EADDRINUSE:
					{
						AddressInUseException exp(__FILE__ ": INETSocket::connect()");
						throw exp;
					}
					break;
				case EINPROGRESS:
					{
						OperationWillBlockException exp(__FILE__ ": INETSocket::connect()");
						throw exp;
					}
					break;
				case EALREADY:
					{
						OperationWillBlockException exp("Previous Connection has not completed: " __FILE__ ": INETSocket::connect()");
						throw exp;
					}
					break;
				case EAGAIN:
					{
						RetryException exp("Previous Connection has not completed: " __FILE__ ": INETSocket::connect()");
						throw exp;
					}
					break;
				case EAFNOSUPPORT:
					{
						TypeNotSupportedException exp("Previous Connection has not completed: " __FILE__ ": INETSocket::connect()");
						throw exp;
					}
					break;
				case EACCES:
				case EPERM:
					{
						SystemDenyException exp("Previous Connection has not completed: " __FILE__ ": INETSocket::connect()");
						throw exp;
					}
				break;
				default:
					{
						SocketException exp("Unknown Exception in SocketServer() : " __FILE__ ": INETSocket::connect()");
						throw exp;
					}
                        } // switch
		}  // if
	} // connect

	// setAddress
	//      Set the address of this socket
	void inet::setAddress(const internet_address& addr)
	{
		m_address = addr;
	} // setAddress

	// setPort
	//      Set the port of this socket
	void inet::setPort(int port)
	{
		m_port = port;
	} // setPort 

} // namespace archendale

#include <SocketObject/SocketServer.h>
#include <ThreadObject/AutoMutex.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

namespace archendale
{

        // TODO:
        //      Need to have it use getprotoent instead of hard coding protocal into socket
        //      Need to update for binding & listening & accepting, perhaps in a socket server
	//	Add in support for reading client information after ::bind()

	// SocketServer:
	//
	SocketServer::SocketServer(const InternetAddress& addr, int port, int backlog) : SocketObject(1)
	{
                m_address = addr;
                m_port = port;
		m_backlog = backlog;
                setSocket(socket(m_address.getType(), SOCK_STREAM, 6));
                if(-1 == getSocket())
                {
			switch(errno)
			{
				case EPROTONOSUPPORT: 
					{
						ProtocolNotSupportedException exp(__FILE__);
						throw exp;
					}
					break;
				case ENFILE:
					{
						OutOfMemoryException exp("Kernel Memory Exhausted : " __FILE__);
						throw exp;
					}
					break;
				case EMFILE:
					{
						Exception exp("Process File Table Overflow in : " __FILE__);
						throw exp;
					}
					break;
				case EACCES:
					{
						AccessDeniedException exp(__FILE__ ":" + __LINE__);
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
				default:
					{
						Exception exp("Unknown Exception in SocketServer() : " __FILE__);
						throw exp;
					}
			} // switch
		} // if
		bind();
		listen();
	} // SocketServer

	// ~SocketServer:
	//
	SocketServer::~SocketServer()
	{
	} // ~SocketServer

        // isWaiting:
        //      RET number of waiting connetions if there is a connection waiting
        int SocketServer::isWaiting()
        {
		AutoMutex mut(m_serverMutex);
		NotImplementedException exp;
		throw exp;
        } // isWaiting

        // getWaitingConnection:
        //      
        INETSocket SocketServer::getWaitingConnection()
        {
		AutoMutex mut(m_serverMutex);
		INETSocket inetsocket;
		sockaddr_in clientInformation;
		socklen_t len = sizeof(clientInformation);
		int socket = accept(getSocket(), (sockaddr*) &clientInformation, &len);
		if(-1 == socket)
		{
			switch(errno) 
			{
			case EAGAIN:
				{	
					OperationWillBlockException exp(__FILE__);
					throw exp;
				}
				break;	
			case EBADF:
				{	
					InvalidSocketDescriptorException exp(__FILE__);
					throw exp;
				}
				break;	
			case ENOTSOCK:
				{	
					NotSocketDescriptorException exp(__FILE__);
					throw exp;
				}
				break;	
			case EOPNOTSUPP:
				{	
					NotSupportedException exp("SocketServer::accept() -" __FILE__);
					throw exp;
				}
				break;	
			case EFAULT:
				{	
					Exception exp(__FILE__ " - Address out of user space");
					throw exp;
				}
				break;	
			case EPERM:
				{	
					FirewallDeniedConnectionException exp(__FILE__);
					throw exp;
				}
				break;	
			default:
				{
					Exception exp("Unknown error in SocketServer::getWaitingConnection");
					throw exp;
				}
			} // switch
		} // if
		InternetAddress addr;
		addr.addAddress(inet_ntoa(clientInformation.sin_addr));
		inetsocket.setSocket(socket);
		inetsocket.setPort(ntohs(clientInformation.sin_port));
		inetsocket.setAddress(addr);

		return inetsocket;
        } // getWaitingConnection

        // bind:
        //      binds the current socket
        void SocketServer::bind()
        {
                sockaddr_in socketAttribute;
                socketAttribute.sin_family = m_address.getType();
                socketAttribute.sin_port  = htons(m_port);
                inet_aton(m_address.getAddress().c_str(), &socketAttribute.sin_addr);
                if(::bind(getSocket(), (sockaddr*) &socketAttribute, sizeof(socketAttribute)))
                {
			switch(errno) 
			{
			case EBADF:
				{	
					NotSocketDescriptorException exp(__FILE__);
					throw exp;
				}
				break;	
			case EINVAL:
				{	
					SocketBoundException exp(__FILE__);
					throw exp;
				}
				break;	
			case EACCES:
				{	
					AccessDeniedException exp("User is not Super User : " __FILE__);
					throw exp;
				}
				break;	
			case ENOTSOCK:
				{	
					NotSocketDescriptorException exp("Argument is a file descriptor, not a socket descriptor : " __FILE__);
					throw exp;
				}
				break;	
			default:
				{
					Exception exp("Unknown error in SocketServer::bind() : " __FILE__);
				}
				break;
			} // switch
                }  // if
        } // bind 

        // listen:
        //      binds the current socket
        void SocketServer::listen()
        {
		if(-1 == ::listen(getSocket(), m_backlog)) 
		{
			switch(errno)
			{
			case EBADF:
				{
					InvalidSocketDescriptorException exp(__FILE__);
					throw exp;
				}
				break;
			case ENOTSOCK:
				{
					NotSocketDescriptorException exp(__FILE__);
					throw exp;
				}
				break;
			case EOPNOTSUPP:
				{
					NotSupportedException exp("SocketServer::listen() Listen not supported - " __FILE__);
					throw exp;
				}
				break;	
			default:
				{
					Exception exp("SocketServer::listen() - Unknown error");
					throw exp;
				}
				break;	
			} // switch
		} // if
        } // listen

} // namespace archendale

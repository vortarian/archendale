#include <socket/server.h>
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
	SocketServer::SocketServer(const InternetAddress& addr, int port, int backlog) : Socket(1), m_protocolName("tcp")
	{
                m_address = addr;
                m_port = port;
		m_backlog = backlog;
                // Get the protocol id from the system
                // TODO: this is specific to BSD systems, find POSIX method
                protoent* protocol = getprotobyname(m_protocolName.c_str());
                if(protocol == 0)
                {
                        // Either the file does not exist, or there is some other error
                        string error =
                                __FILE__
                                ": SocketServer::SocketServer() : "
                                "Unable to get the protocol ";
                        error += m_protocolName;
                        Exception exp(error);
                        throw exp;
                } // if
		int socketDescriptor = socket(m_address.getType(), SOCK_STREAM, protocol->p_proto);
                if(-1 != socketDescriptor) 
		{
			setSocket(socketDescriptor);
		} else
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
						SocketException exp("Unknown Exception in SocketServer() : " __FILE__);
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
			case EOPNOTSUPP:
				{	
					NotSupportedException exp("SocketServer::accept() -" __FILE__);
					throw exp;
				}
				break;	
			case EFAULT:
				{	
					SocketException exp(__FILE__ " - Address out of user space");
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
					SocketException exp("Unknown error in SocketServer::getWaitingConnection");
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
                if(-1 == ::bind(getSocket(), (sockaddr*) &socketAttribute, sizeof(socketAttribute)))
                {
			switch(errno) 
			{
			case EBADF:
				{	
					NotDescriptorException exp(__FILE__);
					throw exp;
				}
				break;	
			case EINVAL:
				{	
					BoundException exp(__FILE__);
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
					NotDescriptorException exp("Argument is a file descriptor, not a socket descriptor : " __FILE__);
					throw exp;
				}
				break;	
			default:
				{
					SocketException exp("Unknown error in SocketServer::bind() : " __FILE__);
					throw exp;
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
			case EOPNOTSUPP:
				{
					NotSupportedException exp("SocketServer::listen() Listen not supported - " __FILE__);
					throw exp;
				}
				break;	
			default:
				{
					SocketException exp("SocketServer::listen() - Unknown error");
					throw exp;
				}
				break;	
			} // switch
		} // if
        } // listen

} // namespace archendale

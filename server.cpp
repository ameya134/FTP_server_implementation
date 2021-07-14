#include "server.h"
#include "packets.h"

#include <cstring> /* include for c functions like memset, memcpy */


FTPServer::FTPServer(const std::string& root, int port)
	: m_port(port), m_root(root)
{
	std::cout << "server object created..." << std::endl;
	return;
}

int FTPServer::serverInitialize(void)
{
	/* create a server socket */
	m_sock_server = socket(AF_INET,SOCK_STREAM,0);
	if(m_sock_server == -1){
		printf("error creating socket...\n");
		return -1;
	}

	/* clear the structure memory and fill in the data */
	memset((void *)&m_serverAddr,0,sizeof(m_serverAddr));

	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_serverAddr.sin_port = htons(m_port);

	/* bind the socket to a port and addr */
	if( bind(m_sock_server, (struct sockaddr *) &m_serverAddr, sizeof(struct sockaddr)) < 0 ){

		printf("error binding socket...\n");
	}

	std::cout << "FTP server Initialized..." << std::endl;
	return 0;
}

void FTPServer::registerUserCallback(void (*userCallback) (void *params))
{
	m_userCallback = userCallback;
	std::cout << "callback registered..." << std::endl;
	
	return;
}

int FTPServer::runService(void)
{
	while(1){
		/* listen on the socket for any connection requests */
		if(listen(m_sock_server,MAXPENDING) < 0){
			printf("failed to listen for connections...\n");
		}
	}

	return 0;
}

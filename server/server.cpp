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
	/* listen on the socket for any connection requests */
	if(listen(m_sock_server,MAXPENDING) < 0){
		printf("failed to listen for connections...\n");
	}
	
	printf("Listning for connection requests on port %d\n",m_port);

	m_clientAddrLen = sizeof(m_clientAddr);
	while(1){
		if(m_sock_client = accept(m_sock_server,(struct sockaddr *)&m_clientAddr, &m_clientAddrLen ) < 0 ){
			std::cout << "failed to accept any new connections" << std::endl;
		}

		std::cout << "connection established" << std::endl;
		handleConnection();
	}

	return 0;
}


void FTPServer::handleConnection(void)
{
	packet_t dataBuf;

	/* clear the dataBuf */
	memset(&dataBuf,0,sizeof(dataBuf));
	printf("packet buffer cleared...\n");
	
	while (strncmp(dataBuf.payload,"close",5)){
		
		/* receive the metadata for the packet */
		recv(m_sock_client,&dataBuf.metaData,sizeof(dataBuf.metaData),0);
		
		printf("received metadata from client...\n");
		printf("length of packet = %d\n",dataBuf.metaData.payload_len);
		std::cout << dataBuf.metaData.packetType << " "
			<< dataBuf.metaData.payload_len << std::endl;
		
		/* receive the packet using packet length from metadata */
		recv(m_sock_client,&dataBuf.payload,dataBuf.metaData.payload_len,0);
		
		for(int i=0;i<dataBuf.metaData.payload_len;i++){
			std::cout << dataBuf.payload[i];
		}
		std::cout << std::endl;

		send(m_sock_client,dataBuf.payload,dataBuf.metaData.payload_len,0);

		close(m_sock_client);
		return;
	}
	
}

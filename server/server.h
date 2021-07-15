#pragma once
#include <iostream>
#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define MAXPENDING 5 /* max pending connection requests for socket */

class FTPServer{

private:
	const std::string m_root;
	int m_port;
	int m_sock_server, m_sock_client;
	struct sockaddr_in m_serverAddr;
	struct sockaddr_in m_clientAddr;
	unsigned int m_clientAddrLen;
	void (*m_userCallback) (void *params);


private:
	void handleConnection(void);

public:
	FTPServer(const std::string& root, int port);
	int serverInitialize(void);
	void registerUserCallback(void (*userCallback)(void *params));
	int runService(void);

};

#pragma once
#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define MAXPENDING 5 /* max pending connection requests for socket */

class FTPServer{

private:
	const std::string m_root;
	int m_port;
	int m_sock_server;
	struct sockaddr_in m_serverAddr;
	void (*m_userCallback) (void *params);

public:
	FTPServer(const std::string& root, int port);
	int serverInitialize(void);
	void registerUserCallback(void (*userCallback)(void *params));
	int runService(void);

};

#include <iostream>
#include "server.h"


void myCallbackFunc(void *params)
{
	std::cout << "user callback function..." << std::endl;
}

int main(int argc, char **argv)
{
	std::cout << "starting FTP server...." << std::endl;

	/* create FTP server on port 1234 */
	FTPServer server("/home/skywalker/dev/cpp/myFTP_server/root",1234);

	/* register user callback */
	server.registerUserCallback(myCallbackFunc);

	/* initialize and setup the server */
	server.serverInitialize();

	if(server.runService() < 0)
	{
		std::cout << "error executing server run" << std::endl;
		return -1;
	}else{
		std::cout << "server terminated successfully" << std::endl;
	}

	return 0;
}

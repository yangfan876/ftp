#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "ftp_shell.h"
#include "ftp.h"

void ls_send(int ctlfd, struct sockaddr_in *server_addr,\
			CTL *ctl)
{
	char buf[20];

	memset(buf, 0, 20);
	send(ctlfd, ctl, sizeof(CTL), 0);
	recv(ctlfd, buf, 20, 0);
	printf("%s\t", buf);
	printf("\n");
}

void push_send(int ctlfd, struct sockaddr_in *server_addr,\
			CTL *ctl)
{
	struct sockaddr_in server;
	int datafd;

	send(ctlfd, ctl, sizeof(CTL), 0);
	sleep(1);

	server.sin_family = AF_INET;
	server.sin_port = htons(DATP);
	server.sin_addr.s_addr = server_addr->sin_addr.s_addr;
	
	if ((datafd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("DATA SOCKET");
		exit(1);
	}

	if (connect(datafd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("DATA CONNECT");
		exit(1);
	}

	send(datafd, "ask to push", 11, 0);

	close(datafd);

/*	while ()
	{
		
	}*/
	
}

void pull_send(int ctlfd, struct sockaddr_in *server_addr,\
			CTL *ctl)
{

}




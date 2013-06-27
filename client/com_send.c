#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "ftp_shell.h"
#include "ftp.h"

void ls_send(int ctlfd, struct sockaddr_in *server_addr,\
			CTL *ctl)
{
	char buf[1000];

	memset(buf, 0, 1000);
	send(ctlfd, ctl, sizeof(CTL), 0);
	recv(ctlfd, buf, 1000, 0);
	printf("%s\t", buf);
	printf("\n");
}

void push_send(int ctlfd, struct sockaddr_in *server_addr,\
			CTL *ctl)
{
	struct sockaddr_in server;
	int datafd;
	char sendbuf[100];

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

	int fd;

	memset (sendbuf, 0, 100);

	fd = open(ctl->file, O_RDONLY);
	
	int tmp = 0;

	while ((tmp = read(fd, sendbuf, 80)) >= 80)
	{
		send(datafd, sendbuf, tmp, 0);
		memset(sendbuf, 0, 80);
	}

	send(datafd, sendbuf, tmp, 0);

	close(fd);
	close(datafd);

}

void pull_send(int ctlfd, struct sockaddr_in *server_addr,\
			CTL *ctl)
{
	char recvbuf[100];

	send(ctlfd, ctl, sizeof(CTL), 0);

	int fd;
	fd = open(ctl->file, O_CREAT|O_RDWR, 0644);

	int tmp = 0;

	while ((tmp = recv(ctlfd, recvbuf, 80, 0)) >= 80)
	{
		write(fd, recvbuf, tmp);
		memset(recvbuf, 0, 100);
	}
	write(fd, recvbuf, tmp);
	
	close(fd);
}




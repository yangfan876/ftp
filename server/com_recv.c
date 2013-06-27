#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include "ftp_shell.h"
#include "ftp.h"

void ls_recv(int ctlfd, CTL *ctl)
{
	DIR *dir_ptr;
	struct dirent *dir_ent;
	char buf[1000];
	int i = 0;
	
	memset(buf, 0, 1000);

	dir_ptr = opendir("./ftp");

	while ((dir_ent = readdir(dir_ptr)) != NULL)	
	{
		strcpy(&buf[i], dir_ent->d_name);
		i += strlen(dir_ent->d_name);
		buf[i] = '\t';
		i += 1;

	}
	buf[i] = '\0';
	
	
	send(ctlfd, buf, strlen(buf), 0);
}

void push_recv(int ctlfd, CTL *ctl)
{
	int datafd, dataClient;
	int value = 1;
	char recvbuf[100];
	struct sockaddr_in server_get;
	int sin_size = sizeof (struct sockaddr_in);
	
	server_get.sin_family = AF_INET;
	server_get.sin_port = htons(DATP);
	server_get.sin_addr.s_addr = INADDR_ANY;

	if ((datafd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("DATA SOCEKT");
		exit(1);
	}

	setsockopt(datafd, SOL_SOCKET, SO_REUSEADDR, &value, \
				sizeof(value));
	
	if (bind(datafd, (struct sockaddr *)&server_get, sizeof (server_get)) == -1)
	{
		perror("DATA BIND");
		exit(1);
	}
	
	if (listen(datafd, 5) == -1)
	{
		perror("DATA LISTEN");
		exit(1);
	}

	if ((dataClient = accept(datafd,\
			(struct sockaddr *)&server_get, &sin_size)) == -1)
	{
		perror("ACCEPT");
		exit(1);
	}

	memset(recvbuf, 0, 100);
	int fd;
	char path[20];

	strcpy(path, "./ftp/");
	strcpy(&path[6], ctl->file);

	fd = open(path, O_CREAT|O_RDWR, 0644);
	
	int tmp = 0;

	while ((tmp = recv(dataClient, recvbuf, 80, 0)) >= 80)
	{
		write(fd, recvbuf, tmp);
		memset(recvbuf, 0, 100);
	}

	write(fd, recvbuf, tmp);

	close(fd);
	close(datafd);
	close(dataClient);

}

void pull_recv(int ctlfd, CTL *ctl)
{
	char sendbuf[100];
	
	memset(sendbuf, 0, 100);
	
	int fd;
	char path[20];

	strcpy(path, "./ftp/");
	strcpy(&path[6], ctl->file);


	fd = open(path, O_RDONLY);

	int tmp = 0;

	while ((tmp = read(fd, sendbuf, 80)) >= 80)
	{
		send(ctlfd, sendbuf, tmp, 0);
		memset(sendbuf, 0, 80);
	}

	send(ctlfd, sendbuf, tmp, 0);

	close(fd);
}

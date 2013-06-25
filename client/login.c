#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ftp.h"

int login(const char *user, const char *target)
{
	struct sockaddr_in addr;
	int tmp;
	int ctlfd;
	char confirm_buf[12];

	memset(&addr, 0, sizeof (struct sockaddr_in));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(CTLP);

	tmp = inet_pton(AF_INET, target, &addr.sin_addr);
	
	if (tmp == 0)
	{
		return 0;
	}
	else if (tmp == -1)
	{
		return -1;
	}

	if ((ctlfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("SOCKET");
		exit(1);
	}


	if (connect(ctlfd, (struct sockaddr *)&addr, sizeof (addr)) == -1)
	{
		perror("CONNECT");
		exit(1);
	}

	if (send(ctlfd, user, strlen (user), 0) == -1)
	{
		perror("SEND");
	}

	recv(ctlfd, confirm_buf, 12, 0);
	confirm_buf[12] = 0;
	printf("%s\n", confirm_buf);
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#include "ftp.h"

main()
{
	int Sctlfd, ctlfd;
	struct sockaddr_in addr;
	int sin_size = sizeof (struct sockaddr_in);
	char buf[10] = {0};
	int value = 1;

	memset (&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(CTLP);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	if ((Sctlfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("SOCKET");
		exit (1);
	}
	
	setsockopt(Sctlfd, SOL_SOCKET, SO_REUSEADDR, &value,\
				sizeof(value));

	if (bind(Sctlfd, (struct sockaddr *)&addr, sizeof (addr)) == -1)
	{                                          
		perror("BIND");
		exit(1);
	}

	if (listen(Sctlfd, 5) == -1)
	{
		perror("LISTEN");
		exit(1);
	}
	
	if ((ctlfd = accept(Sctlfd, (struct sockaddr *)&addr,\
			&sin_size)) == -1)
	{
		perror("ACCEPT");	
		exit(1);
	}

	recv(ctlfd, buf, 10, 0);
	
	sleep(2);
	
	send(ctlfd, "confirmed ok", 12, 0);
	
	printf("%s\n", buf);	
  

}

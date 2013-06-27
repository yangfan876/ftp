#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include "ftp_shell.h"
#include "com_send.h"

void ftp_shell(int ctlfd, struct sockaddr_in *server_addr)
{
	CTL ctl;
	int i = 0;
	printf("in the ftp shell.\n");

	while (1)
	{
		char info[20];
		int flag;

		memset((void *)&ctl, 0, sizeof(CTL));
		printf(">>>");
		fgets(info, 20, stdin);
		fflush(stdin);
		flag = handle_com(&ctl, info, 20);

		if (flag == -1)
		{
			printf("no this commond.\n");
			continue;
		}	
		else if (flag == 1)
		{
			return;
		}

		if (ctl.comflag == PUSH || ctl.comflag == PULL)
		{ 
			char *p;
			p = ctl.file;
			while (p[i] != '\n')
				i++;
			p[i] = '\0';
		}
/*test print*/		
		if (ctl.comflag == PUSH || ctl.comflag == PULL)
		{
			printf ("%s %s\n", ctl.comname, ctl.file);
		}
		else
			printf("%s\n", ctl.comname);	
/*test print*/		
		
		if (ctl.comflag == LS)
		{
			ls_send(ctlfd, server_addr, &ctl);
		}
		else if (ctl.comflag == PUSH)
		{
			push_send(ctlfd, server_addr, &ctl);
		}
		else if (ctl.comflag == PULL)
		{
			pull_send(ctlfd, server_addr, &ctl);
		}

	}	
}

int handle_com(CTL *ctl, char *info, int lenth)
{
	char *p = info;
	int i = 0;
	while (i < lenth)
	{
		if (p[i] == ' ')
		{
			p[i] = '\0';
			break;
		}
		else if (p[i] == '\n')
		{
			break;
		}
		i++;
	}

	if (!strncmp(info, "ls", 2))
	{
		strncpy(ctl->comname, "ls", 2);
		ctl->comflag = LS;
		return 0;
	}

	else if (!strncmp(info, "pull", 4))
	{
		strncpy(ctl->comname, "pull", 4);
		ctl->comflag = PULL;
		strcpy(ctl->file, &p[i+1]);
		return 0;
	}

	else if(!strncmp(info, "push", 4))
	{
		strncpy(ctl->comname, "push", 4);
		ctl->comflag = PUSH;
		strcpy(ctl->file, &p[i+1]);
		return 0;
	}

	else if(!strncmp(info, "exit", 4))
	{
		printf("Bye ~_~ \n\n");
		exit(1);
	}
	else
	{
		return -1;
	}
}

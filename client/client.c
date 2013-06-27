#include <stdio.h>
#include <stdlib.h>


void welcome(void);


void main(int argc, char **argv)
{
	welcome();

	if (argc > 1)
	{
		int try = 3;
		while (try--)
		{
			if (!login(argv[1], argv[2]))
			{
				printf("login failed.\n");
				exit(1);
			}		
		}

		printf("Permission denied\n");
		exit(1);
	}
	else
	{
		ftp_shell(-1, (struct sockaddr_in *)NULL);
		exit(1);
	}
}

void welcome(void)
{
	printf("%s\n%s\n%s\n", \
			"Welcome to use this ftp server", 
			"I just play a joke", \
			"This is just a test");
}

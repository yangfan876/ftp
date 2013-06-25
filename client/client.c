#include <stdio.h>

#include <unistd.h>


void welcome(void);


main(int argc, char **argv)
{
	welcome();

	if (argc > 1)
	{
		login(argv[1], argv[2]);
	}
	else
	{
//		ftp_shell();
	}
}

void welcome(void)
{
	printf("%s\n%s\n%s\n", \
			"Welcome to use this ftp server", 
			"I just play a joke", \
			"This is just a test");
}

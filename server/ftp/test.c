#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

main()
{
	int fd;
	char buf[100];
	memset(buf, 0, 100);
	fd = open("1.c", O_CREAT|O_RDWR, 0644);

	write(fd, "1111111111", 10);

	close(fd);

}

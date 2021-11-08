#include <stdio.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
//#include "./get_next_line.h"
#include <time.h>
int main(int argc, char **argv)
{
	int fd;
	char *ret = NULL;
	int line;
	time_t begin = time(0);

	line = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((ret = get_next_line(fd) != NULL)
			printf("Line #%d: %s\n", ret, ++line);
		if (!ret)
			printf("-----------\nNO line or Error\n");
		close(fd);
	}
	if (argc == 1)
	{
		while ((ret = get_next_line(0)) != NULL)
			printf("Line #%d: %s\n", ret, ++line);
		if (!ret)
			printf("-----------\nNO line or Error\n");
		close(fd);
	}
	
	time_t end = time(0);
	printf("Begin time : %ld\n", begin);
	printf("End Time : %ld\n", end);
	printf("It tasks : (%ld)s\n", end-begin);
	
	return (0);
}

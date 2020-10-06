#include "get_next_line.h"

int    main(int ac, char **av)
{
	int    fd;
    char    *line;
    int n = 1;
	(void)ac;

	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = 0;
	while (n == 1)
	{
		n = get_next_line(fd, &line);
		//printf("[%d]" , n);
    	printf("%s\n", line);
		free(line);
	}
//	while(1);
}

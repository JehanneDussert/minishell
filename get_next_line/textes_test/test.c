#include "get_next_line.h"

int	main()
{
	char **line;
	char buf[BUFFER_SIZE + 1];
	int fd;

	fd = open("text.txt", O_RDONLY);
	read(fd, buf, BUFFER_SIZE);
	
	buf[BUFFER_SIZE] = '\0';
	if (!(line[0] = ft_strjoin(line[0], buf)))
		write(1, "c mor lol", 9);
	printf("%s", line[0]);
	return(0);
}

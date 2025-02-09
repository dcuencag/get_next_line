
#include "get_next_line.h"

int	main(void)
{
	char *storage = malloc(sizeof(char *) * BUFER_SIZE + 1);
	int fd = open("text.txt", O_RDONLY);
	int counter;

	if (fd == -1)
	{
		perror("Error abriendo archivo");
		return (1);
	}

	counter = 0;
	while (counter < 10)
	{
		read(fd, storage, BUFER_SIZE);
		printf("%s\n\n", storage);
		counter++;
	}
	printf("%s\n\n", storage);
	return (0);
}
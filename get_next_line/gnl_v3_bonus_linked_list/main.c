
#include "get_next_line_bonus.h"

int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;
	char *line;

	fd1 = open("../../tests_GNL/my_tests_gnl/fable_small.txt", O_RDONLY);
	fd2 = open("../../tests_GNL/my_tests_gnl/file_test_nl.txt", O_RDONLY);
	fd3 = open("../../tests_GNL/my_tests_gnl/file_test_no_nl.txt", O_RDONLY);
	 
	line = get_next_line(fd1);
	printf("result 1: %s\n\n", line);
	line = get_next_line(fd2);
	printf("result 2: %s\n\n", line);
	line = get_next_line(fd3);
	printf("result 3: %s\n\n", line);
	line = get_next_line(fd3);
	printf("result 3: %s\n\n", line);
	line = get_next_line(fd2);
	printf("result 2: %s\n\n", line);
	line = get_next_line(fd3);
	printf("result 3: %s\n\n", line);
	line = get_next_line(fd1);
	printf("result 1: %s\n\n", line);
	line = get_next_line(fd2);
	printf("result 2: %s\n\n", line);
	// free(line);
	return (0);
}

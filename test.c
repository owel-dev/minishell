#include "src/minishell.h"

void print()
{
	printf("hello\n");
}

int main()
{
	// while (1){}
	// printf("hello");

	int status;
	int pid ;
	int i = 0;

	// while (i < 100)
	// {
		pid = fork();

		if (pid == 0)
		{
			exit(255);
		}
		waitpid(pid, &status, 0);
	// 	// printf("\n%d\n", 256 << 1);
	// 	printf("\n%d = %d\n", i, status);
	// 	printf("%d\n", i << 8);
	// 	i++;
	// }
	printf("hello\n");
}




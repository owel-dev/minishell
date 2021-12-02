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
	int pid = fork();
	signal(SIGCHLD, print);

	if (pid == 0)
	{
		// while(1){}
	}
	waitpid(pid, &status, 0);
	printf("\n%d\n", status);
}




#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	int i;
	int status;

	status = 99;
	int pid = fork();
	if (pid == 0)
	{
		i = execve("/bin/ls2", av, env);
		exit(1);
	}
	waitpid(pid, &status, 0);
	printf("status: %d\n", status);
}

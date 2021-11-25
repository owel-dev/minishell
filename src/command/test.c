#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	int pid = fork();
	if (pid == 0)
	{
		execve("/bin/ls", av, env);
	}
	waitpid(pid, NULL, 0);
	printf("%s", av[0]);
}

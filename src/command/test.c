#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	int i;
	int status;

	status = 99;
	int pid = fork();
	if (pid == 0)
	{
<<<<<<< HEAD
		execve("/bin/ls", av, env);
	}
	waitpid(pid, NULL, 0);
	printf("%s", av[0]);
=======
		i = execve("/bin/ls2", av, env);
		exit(1);
	}
	waitpid(pid, &status, 0);
	printf("status: %d\n", status);
>>>>>>> 538129888f0d8a1236c18aabc04cc7b2087c40a5
}

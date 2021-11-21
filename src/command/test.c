#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	execve("/bin/ls", av, env);
}

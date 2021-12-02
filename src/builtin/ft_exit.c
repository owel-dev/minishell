#include "../minishell.h"

int ft_exit(t_bundle *bundle)
{
	write(1, "logout\n", 7);
	exit(0);
}


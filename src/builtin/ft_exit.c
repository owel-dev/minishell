#include "../minishell.h"

int ft_isallnum(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int ft_exit(t_bundle *bundle)
{
	if (bundle->token->next)
	{
		if (!ft_isallnum(bundle->token->next->content))
		{
			printf("bash: exit: %s: numeric argument required\n", \
				bundle->token->next->content);
		}
	}
	write(1, "logout\n", 7);
	exit(7);
}


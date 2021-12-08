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

int builtin_exit(t_bundle *bundle)
{
	write(1, "logout\n", 7);
	if (bundle->token->next)
	{
		if (!ft_isallnum(bundle->token->next->content))
		{
			printf("bash: exit: %s: numeric argument required\n", \
				bundle->token->next->content);
		}
	}
	exit(0);
}


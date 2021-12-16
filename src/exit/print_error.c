#include "../minishell.h"

void	print_error_exit(char *str, int error_num)
{
	printf("%s222\n", str);
	exit(error_num);
}

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

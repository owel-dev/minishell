#include "minishell.h"

void	parsing(char *str)
{
	char	**space;
	int		i;

	space = ft_split(str, ' ');
	if (space == NULL)
		print_error("SPACE_SPLIT_ERROR");
	i = 0;
	while (space[i])
		printf("%s\n", space[i++]);
}

void	split_command(char *str)
{
	char	**semi;
	int		i;

	semi = ft_split(str, ';');
	if (semi == NULL)
		print_error("SEMI_SPLIT_ERROR");
	i = 0;
	while(semi[i])
		parsing(semi[i++]);
}

int	main(void)
{
	char *input;

	while(1)
	{
		input = readline("input: ");
		if (input == NULL)
			break ;
		else
		{
			split_command(input);
		}
		// printf("%s\n", input);
	}

}

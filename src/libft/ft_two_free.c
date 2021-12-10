#include "libft.h"

void	ft_two_free(char **result)
{
	int		i;

	if (result == NULL)
		return ;
	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	free(result);
	return ;
}

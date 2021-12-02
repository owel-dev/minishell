/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:23:10 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/01 19:37:05 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_fdnum(char *str, int back)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	if (str == NULL)
		return (0);
	if (back && str[i] == '&')
	{
		fd = 2;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (fd);
}

void	init_fd(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
}

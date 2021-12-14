/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:23:10 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/14 20:20:49 by ulee             ###   ########.fr       */
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

void	dup_redir_fd(t_bundle *bundle)
{
	if (bundle->token->fd[0] == -1 || bundle->token->fd[1] == -1)
	{
		printf("%s\n", bundle->error_msg);
		exit(FAIL);
	}
	if (bundle->token->fd[0] > -1)
		dup2(bundle->token->fd[0], STDIN_FILENO);
	if (bundle->token->fd[1] > -1)
		dup2(bundle->token->fd[1], STDOUT_FILENO);
}

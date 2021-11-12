/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:24:11 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/12 14:23:22 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_handler(t_token *token)
{
	int	pid;
	int status;

	pid = fork();
	if (pid < 0)
		print_error("FORK_ERROR");
	if (pid == 0)
	{
		if (is_fdnum(token->pre->content, 0) == 1 && token->pre->back_space == 0)
		{
			dup2(token->pre->content[0] + '0', STDIN_FILENO);
		}
		if (is_fdnum(token->next->content, 1) == 2 && token->pre->back_space == 0)
		{
			dup2(ft_atoi(token->next->content[1] +'0' ), STDOUT_FILENO);
		}
	}
	else
	{
		wait(&status);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:24:11 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/12 16:25:38 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	d_redir_cmd(t_bundle *bundle, t_token *token)
{
	int	fd;

	fd = set_fd(token);
	if (fd < 0)
	{
		if (token->token_type == D_REDIR_OUT)
		{
			fd = open(token->next->content, O_WRONLY | O_APPEND | O_CREAT, 0666);
		}
		if (token->token_type == D_REDIR_IN)
		{
			while ()
			{
				
			}
			
			fd = open(token->next->content, 
		}
	}
	else
}

int	redir_cmd(t_bundle *s_bundle, t_token *token)
{
	
}

int	set_fd(t_token *token)
{
	if (is_fdnum(token->pre->content, 0) == 1 && token->pre->back_space == 0)
		return (token->pre->content[0] + '0');
	else if (is_fdnum(token->next->content, 1) == 2 && token->pre->back_space == 0)
		return (token->pre->content[1] + '0');
	return (-1);
}

int	redir_handler(t_bundle *bundle, t_token *token)
{
	int	pid;
	int status;

	pid = fork();
	if (pid < 0)
		print_error("FORK_ERROR");
	if (pid == 0)
	{
		
		if (token->token_type == D_REDIR_IN || token->token_type == D_REDIR_OUT)
		{
			d_redir_cmd(bundle, token);
		}
		else if (token->token_type == REDIR_IN || token->token_type == REDIR_OUT)
		{
			redir_cmd(bundle, token);
		}
		execute_cmd();
	}
	else
	{
		wait(&status);
	}
}

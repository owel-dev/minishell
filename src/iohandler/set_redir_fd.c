/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 03:18:22 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/24 23:14:07 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	d_redir_in(t_bundle *bundle)
{
	if (bundle->token->fd[0] > -1)
		dup2(bundle->token->fd[0], STDIN_FILENO);
	if (bundle->token->fd[0] < 0)
	{
		if (bundle->token->fd[0] < 0)
			return (print_error("d_redir_in open file error", EXIT_FAILURE));
	}
	dup2(bundle->token->fd[0], STDOUT_FILENO);
	read_here_document(bundle);
	return (SUCCESS);
}

int	d_redir_out(t_bundle *bundle)
{
	if (bundle->token->fd[0] > -1)
		dup2(bundle->token->fd[1], STDOUT_FILENO);
	if (bundle->token->fd[1] < 0)
	{
		bundle->token->fd[1] = open(bundle->token->next->content, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (bundle->token->fd[1] < 0)
			return (print_error("d_redir_out open file error", FAIL));
		dup2(bundle->token->fd[1], STDIN_FILENO);
		bundle->token = bundle->token->next->next;
	}
	else
	{
		dup2(bundle->token->fd[1], STDIN_FILENO);
		bundle->token = bundle->token->next;
	}
	return (SUCCESS);
}

int	redir_out(t_bundle *bundle)
{
	if (bundle->token->fd[0] > -1)
	{
		dup2(bundle->token->fd[0], STDIN_FILENO);
	}
	if (bundle->token->fd[1] < 0)
	{
		bundle->token->fd[1] = open(bundle->token->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (bundle->token->fd[1] < 0)
			return (print_error("redir_out open file error", FAIL));
		dup2(bundle->token->fd[1], STDOUT_FILENO);
		bundle->token = bundle->token->next->next;
	}
	else
	{
		dup2(bundle->token->fd[1], STDOUT_FILENO);
		bundle->token = bundle->token->next;
	}
	return (SUCCESS);
}

int	redir_in(t_bundle *bundle)
{
	if (bundle->token->fd[0] > -1)
		dup2(bundle->token->fd[0], STDIN_FILENO);
	if (bundle->token->fd[1] < 0)
	{
		bundle->token->fd[1] = open(bundle->token->next->content, O_RDONLY);
		if (bundle->token->fd[1] < 0)
			return (print_error("redir_in opne file error", FAIL));
		dup2(bundle->token->fd[1], STDIN_FILENO);
		bundle->token = bundle->token->next->next;
	}
	else
	{
		dup2(bundle->token->fd[1], STDIN_FILENO);
		bundle->token = bundle->token->next;
	}
	return (SUCCESS);
}

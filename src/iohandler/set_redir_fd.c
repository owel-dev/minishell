/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 03:18:22 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/29 02:42:15 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	d_redir_in(t_bundle *bundle)
{
	if (bundle->token->fd[0] > -1)
		dup2(bundle->token->fd[0], STDIN_FILENO);
	read_here_document(bundle);
	bundle->token = bundle->token->next;
	return (SUCCESS);
}

int	d_redir_out(t_bundle *bundle)
{
	if (bundle->token->fd[0] > -1)
		dup2(bundle->token->fd[0], STDIN_FILENO);
	if (bundle->token->fd[1] < 0)
	{
		bundle->token->fd[1] = open(bundle->token->next->content, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (bundle->token->fd[1] < 0)
			print_error_exit("d_redir_out open file error", FAIL);
		dup2(bundle->token->fd[1], STDOUT_FILENO);
		bundle->token = bundle->token->next;
	}
	else
		dup2(bundle->token->fd[1], STDOUT_FILENO);
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
			print_error_exit("redir_out open file error", FAIL);
		dup2(bundle->token->fd[1], STDOUT_FILENO);
		bundle->token = bundle->token->next;
	}
	else
		dup2(bundle->token->fd[1], STDOUT_FILENO);
	return (SUCCESS);
}

int	redir_in(t_bundle *bundle)
{
	if (bundle->token->fd[1] > -1)
		dup2(bundle->token->fd[1], STDOUT_FILENO);
	if (bundle->token->fd[0] < 0)
	{
		bundle->token->fd[0] = open(bundle->token->next->content, O_RDONLY);
		if (bundle->token->fd[0] < 0)
			print_error_exit("No such file or directory", FAIL);
		dup2(bundle->token->fd[0], STDIN_FILENO);
		bundle->token = bundle->token->next;
	}
	else
		dup2(bundle->token->fd[0], STDIN_FILENO);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 03:18:22 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/22 01:46:48 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	d_redir_in(t_bundle *bundle)
{
	int	fd_num[2];

	set_fd(bundle->token, fd_num);
	if (fd_num[0] > -1)
		dup2(fd_num[0], STDIN_FILENO);
	if (fd_num[0] < 0)
	{
		if (fd_num[0] < 0)
			return (print_error("d_redir_in open file error", EXIT_FAILURE));
	}
	dup2(fd_num[0], STDOUT_FILENO);
	read_here_document(bundle);
	return (SUCCESS);
}

int	d_redir_out(t_token *token)
{
	int	fd_num[2];

	set_fd(token, fd_num);
	if (fd_num[0] > -1)
		dup2(fd_num[1], STDOUT_FILENO);
	if (fd_num[1] < 0)
	{
		fd_num[1] = open(token->next->content, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd_num[1] < 0)
			return (print_error("d_redir_out open file error", FAIL));
	}
	dup2(fd_num[1], STDIN_FILENO);
	return (SUCCESS);
}

int	redir_out(t_token *token)
{
	int	fd_num[2];

	set_fd(token, fd_num);
	if (fd_num[0] > -1)
		dup2(fd_num[0], STDIN_FILENO);
	if (fd_num[1] < 0)
	{
		fd_num[1] = open(token->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd_num[1] < 0)
			return (print_error("redir_out open file error", FAIL));
	}
	dup2(fd_num[1], STDOUT_FILENO);
	return (SUCCESS);
}

int	redir_in(t_token *token)
{
	int	fd_num[2];

	set_fd(token, fd_num);
	if (fd_num[0] > -1)
		dup2(fd_num[0], STDIN_FILENO);
	if (fd_num[1] < 0)
	{
		fd_num[1] = open(token->next->content, O_RDONLY);
		if (fd_num[1] < 0)
			return (print_error("redir_in opne file error", FAIL));
	}
	dup2(fd_num[1], STDOUT_FILENO);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 03:18:22 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/20 03:28:46 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	d_redir_in(t_bundle *bundle, t_token *token)
{
	int	fd_num[2];

	set_fd(token, fd_num);
	if (fd_num[0] > -1)
		dup2(fd_num[0], STDIN_FILENO);
	if (fd_num[0] < 0)
	{
		if (fd_num[0] < 0)
			print_error("redir open file error", EXIT_FAILURE);
	}
	dup2(fd_num[0], STDOUT_FILENO);
	read_here_document(bundle);
}

void	d_redir_out(t_token *token)
{
	int	fd_num[2];

	set_fd(token, fd_num);
	if (fd_num[0] > -1)
		dup2(fd_num[0], STDIN_FILENO);
	if (fd_num[0] < 0)
	{
		fd_num[0] = open(token->next->content, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd_num[0] < 0)
			print_error("redir open file error", EXIT_FAILURE);
	}
	dup2(fd_num[0], STDOUT_FILENO);
}

void	redir_out(t_token *token)
{
	int	fd_num[2];

	set_fd(token, fd_num);
	if (fd_num[0] > -1)
		dup2(fd_num[0], STDIN_FILENO);
	if (fd_num[1] < 0)
	{
		fd_num[1] = open(token->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd_num[1] < 0)
			print_error("redir open file error", EXIT_FAILURE);
	}
	dup2(fd_num[1], STDOUT_FILENO);
}

void	redir_in(t_token *token)
{
	int	fd_num[2];

	set_fd(token, fd_num);
	if (fd_num[0] > -1)
		dup2(fd_num[0], STDIN_FILENO);
	if (fd_num[1] < 0)
	{
		fd_num[1] = open(token->next->content, O_RDONLY);
		if (fd_num[1] < 0)
			print_error("redir opne file error", EXIT_FAILURE);
	}
	dup2(fd_num[1], STDIN_FILENO);
}

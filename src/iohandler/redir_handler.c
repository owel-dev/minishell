/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:24:11 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/21 00:44:30 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_readline(int fd[], t_bundle *bundle)
{
	char	*read_doc;

	while (fd[1] > 0)
	{
		read_doc = readline("> ");
		if (!ft_strcmp(read_doc, bundle->token->next->content))
			fd[1] = -1;
		else
			write(fd[1], read_doc, ft_strlen(read_doc));
		free(read_doc);
	}
}

int	read_here_document(t_bundle *bundle)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		get_readline(fd, bundle);
		child_exit(bundle, status);
	}
	else
	{
		waitpid(pid, &status, 0);
		dup2(fd[0], STDIN_FILENO);
	}
	return (0);
}

int	*set_fd(t_token *token, int	fd_num[])
{
	if (is_fdnum(token->pre->content, 0) == 1 && token->pre->back_space == 0)
		fd_num[0] = token->pre->content[0] + '0';
	else
		fd_num[0] = -1;
	if (is_fdnum(token->next->content, 1) == 2 && token->back_space == 0)
		fd_num[1] = (token->pre->content[1] + '0');
	else
		fd_num[1] = -1;
	return (fd_num);
}

void	redir_handler(t_bundle *bundle)
{
	if (bundle->token->token_type == D_REDIR_OUT)
		d_redir_out(bundle->token);
	else if (bundle->token->token_type == D_REDIR_IN)
		d_redir_in(bundle);
	else if (bundle->token->token_type == REDIR_IN)
		redir_in(bundle->token);
	else if (bundle->token->token_type == REDIR_OUT)
		redir_out(bundle->token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:24:11 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/28 20:15:00 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_readline(int fd[], t_bundle *bundle)
{
	char	*read_doc;

	read_doc = readline("heredoc> ");
	while (fd[1] > 0)
	{
		if (!ft_strcmp(read_doc, bundle->token->next->content))
			fd[1] = -1;
		else
			write(fd[1], read_doc, ft_strlen(read_doc));
		free(read_doc);
		read_doc = readline("heredoc> ");
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

void	set_fd(t_token *token)
{
	if (token->pre && is_fdnum(token->pre->content, 0) == 1 &&
	token->pre->back_space == 0)
	{
		token->fd[0] = ft_atoi(token->pre->content);
		tokenlst_delete(token->pre);
	}
	if (token->next && is_fdnum(token->next->content, 1) == 2 && \
	token->back_space == 0)
	{
		token->fd[1] = ft_atoi(ft_strndup(token->pre->content, 1));
		tokenlst_delete(token->next);
	}
}

int	redir_handler(t_bundle *bundle)
{
	if (bundle->token->token_type == D_REDIR_OUT)
		return(d_redir_out(bundle));
	else if (bundle->token->token_type == D_REDIR_IN)
		return (d_redir_in(bundle));
	else if (bundle->token->token_type == REDIR_IN)
		return (redir_in(bundle));
	else if (bundle->token->token_type == REDIR_OUT)
		return (redir_out(bundle));
	return (FAIL);
}

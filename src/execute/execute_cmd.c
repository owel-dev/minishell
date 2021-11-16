/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:35:44 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/16 00:20:26 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*pipe_cmd(t_bundle *bundle, t_token *token)
{
	int	pid;
	int status;
	int fd[2];
	t_token *tem;

	pid = fork();
	if (pid < 0)
		print_error("pipe fork error");
	pipe(fd);
	if (pipe < 0)
		print_error("pipe function error");
	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		return (token);
	}
	else
	{
		clode(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		tem = token->next;
		token = tem;
		while(token->next->content && token->pipe == PIPE)
		{
			tem = token->next;
			token = tem;
		}
		wait(&status);
		return (token);
	}
}

int	execute_cmd(t_bundle *bundle)
{
	int result;
	t_token *temp;

	while (bundle->token->content)
	{
		temp = bundle->token;
		if (bundle->token->pipe == PIPE)
		{
			bundle->token = pipe_cmd(bundle, bundle->token);
			continue ;
		}
		// if (bundle->token->redir > 0)
		// 	redir_cmd();
		if (is_builtin())
		{
			temp = excute_builtin();
		}
		else if (is_simple_cmd())
		{
			temp = is_simple_cmd();
		}
		bundle->token = temp->next;
	}
	return (result);
}

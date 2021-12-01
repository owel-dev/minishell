/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:35:44 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/01 19:37:12 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cmd(t_bundle *bundle)
{
	int	result;

	result = is_builtin(bundle);
	if (result != SUCCESS)
		result = is_bin(bundle);
	return (result);
}

int execute_redir_cmd(t_bundle *bundle)
{
	int		result;
	pid_t	child_ps;
	int		status;
	t_token *temp;

	result = FAIL;
	child_ps = fork();
	if (child_ps < 0)
		return (result);
	if (child_ps == 0)
	{
		while (bundle->token)
		{
			if (bundle->token->pipe == PIPE)
			{
				child_ps = pipe_cmd(bundle);
				if (!child_ps)
					continue ;
			}
			result = set_redir_fd(bundle, bundle->token);
			result = check_cmd(bundle);
			bundle->token = bundle->token->next;
			if (child_ps > 0)
				child_exit(bundle, result);
			if (child_ps == 0)
			{
				close(STDIN_FILENO);
				dup2(0, STDIN_FILENO);
			}
			init_fd();
		}
		exit(result);
	}
	wait(&status);
	result = status;
	return (result);
}

int	execute_cmd(t_bundle *bundle)
{
	int		result;
	pid_t	child_ps;

	child_ps = -1;
	if (bundle->is_redir)
		return (execute_redir_cmd(bundle));
	while (bundle->token)
	{
		if (bundle->token->pipe == PIPE)
		{
			child_ps = pipe_cmd(bundle);
			if (!child_ps)
				continue ;
		}
		result = check_cmd(bundle);
		if (child_ps > 0)
			child_exit(bundle, result);
		if (child_ps == 0)
		{
			close(STDIN_FILENO);
			dup2(0, STDIN_FILENO);
		}
		bundle->token = bundle->token->next;
	}
	return (result);
}

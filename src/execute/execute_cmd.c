/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:35:44 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/08 19:51:15 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_ps(int child_ps, t_bundle *bundle, int result)
{
	if (child_ps > 0)
		child_exit(bundle, result);
	if (child_ps == 0)
	{
		close(STDIN_FILENO);
		dup2(3, STDIN_FILENO);
		close(3);
	}
}

void	reset_fd(t_bundle *bundle)
{
	dup2(3, STDIN_FILENO);
	dup2(4, STDOUT_FILENO);
	if (bundle->head->fd[0] > -1)
	{
		close(bundle->head->fd[0]);
	}
	if (bundle->head->fd[1] > -1)
	{
		close(bundle->head->fd[1]);
	}
	close(3);
	close(4);
}

int	execute_pipe_cmd(t_bundle *bundle)
{
	int		result;
	pid_t	child_ps;
	int		status;

	while (bundle->token)
	{
		if (bundle->token->pipe == PIPE)
		{
			child_ps = pipe_cmd(bundle);
			if (!child_ps)
				continue ;
		}
		result = set_redir_fd(bundle, bundle->token);
		result = execute_builtin(bundle);
		if (result == NO_BUILTIN)
			result = execute_bin(bundle);
		if (result == SUCCESS)
			g_status = 0;
		bundle->token = bundle->token->next;
		handle_ps(child_ps, bundle, result);
		reset_fd(bundle);
	}
	if (result == 0)
		g_status = 0;
	if (result == EXIT_7)
		exit(0);
	if (result != SUCCESS && result != FAIL)
	{
		g_status = result >> 8;
		result = SUCCESS;
	}
	return (result);
}

int	execute_cmd(t_bundle *bundle)
{
	int		result;

	result = FAIL;
	dup2(STDIN_FILENO, 3);
	dup2(STDOUT_FILENO, 4);
	if (bundle->is_pipe)
		return (execute_pipe_cmd(bundle));
	while (bundle->token)
	{
		result = set_redir_fd(bundle, bundle->token);
		result = execute_builtin(bundle);
		if (result == NO_BUILTIN)
			result = execute_bin(bundle);
		else if (result == SUCCESS)
		{
			g_status = 0;
			return (SUCCESS);
		}
		bundle->token = bundle->token->next;
	}
	reset_fd(bundle);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:35:44 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/03 18:50:37 by ulee             ###   ########.fr       */
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
		dup2(0, STDIN_FILENO);
	}
	init_fd();
}

int	execute_cmd(t_bundle *bundle)
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
			handle_ps(child_ps, bundle, result);
		}
		exit(result);
	}
	wait(&status);
	result = status;
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

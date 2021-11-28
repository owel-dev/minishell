/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:35:44 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/28 20:20:49 by hyospark         ###   ########.fr       */
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
	int result;
	pid_t	child_ps;
	int		status;

	result = FAIL;
	child_ps = fork();
	if (child_ps < 0)
		return (result);
	if (child_ps == 0)
	{
		while (bundle->token)
		{
			if (bundle->token->pipe == PIPE)
				child_ps = pipe_cmd(bundle);
			if (is_redir_token(bundle->token))
				result = redir_handler(bundle);
			result = check_cmd(bundle);
			bundle->token = bundle->token->next;
			// if (child_ps)
			// 	child_exit(bundle, result);
		}
		exit(result);
	}
	wait(&status);
	result = status;
	return (result);
}

int	execute_cmd(t_bundle *bundle)
{
	int result;
	pid_t	child_ps;

	child_ps = 0;
	if (bundle->is_redir)
		return (execute_redir_cmd(bundle));
	while (bundle->token)
	{
		if (bundle->token->pipe == PIPE)
			child_ps = pipe_cmd(bundle);
		result = check_cmd(bundle);
		if (!bundle->token)
			break ;
		bundle->token = bundle->token->next;
		// if (child_ps)
		// 	child_exit(bundle, result);
	}
	return (result);
}

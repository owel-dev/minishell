/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:35:44 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/20 18:17:56 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *check_cmd(t_bundle *bundle)
{
	t_token *ret_token;

	ret_token = is_builtin(bundle, bundle->token);
	if (ret_token)
		return (ret_token);
	ret_token = is_bin(bundle, bundle->token);
	if (ret_token)
		return (ret_token);
	return (NULL);
}

int	execute_cmd(t_bundle *bundle)
{
	int result;
	t_token *temp;
	int	child_ps;

	while (bundle->token)
	{
		if (bundle->token->pipe == PIPE)
			child_ps = pipe_cmd(bundle, bundle->token);
		// if (bundle->token->redir > 0)
		// 	redir_cmd();
		result = check_cmd(bundle);
		if (child_ps)
			child_exit(bundle, result);
		bundle->token = temp->next;
	}
	return (result);
}

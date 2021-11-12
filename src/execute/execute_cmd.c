/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:35:44 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/12 17:35:42 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_cmd()
{
	
}

int	execute_cmd(t_bundle *bundle)
{
	int result;
	t_token *temp;

	while (bundle->token->content)
	{
		if (is_builtin())
		{
			temp = excute_builtin();
		}
		else if (is_simple_cmd())
		{
			temp = is_simple_cmd();
		}
		else if (bundle->token->token_type == PIPE)
		{
			
		}
		bundle->token = temp->next;
	}
	return (result);
}

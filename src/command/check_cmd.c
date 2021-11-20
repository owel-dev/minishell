/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:05 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/20 16:41:48 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int is_bin(t_bundle *bundle, t_token *token)
// {

// }

int is_builtin(t_bundle *bundle, t_token *token)
{
	if (token->back_space || token->next->token_type >= REDIR_IN)
	{
		if (ft_strcmp(token->content, "cd") == 0)
			return (ft_cd(token->next));
		else if (ft_strcmp(token->content, "env") == 0)
			return (ft_env(bundle->env, token->next));
		else if (ft_strcmp(token->content, "pwd") == 0)
			return (ft_pwd(token->next));
		else if (ft_strcmp(token->content, "export") == 0)
			return (ft_export(bundle, token->next));
		else if (ft_strcmp(token->content, "unset") == 0)
			return (ft_unset(bundle, token->next));
		else if (ft_strcmp(token->content, "echo") == 0)
			return (ft_echo(token));
	}
	return (FAIL);
}

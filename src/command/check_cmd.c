/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:05 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/21 14:24:18 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int is_bin(t_bundle *bundle, t_token *token)
// {

// }

int is_builtin(t_bundle *bundle)
{
	if (bundle->token->next == NULL || bundle->token->back_space \
	|| bundle->token->next->token_type >= REDIR_IN)
	{
		if (ft_strcmp(bundle->token->content, "cd") == 0)
			return (ft_cd(bundle));
		else if (ft_strcmp(bundle->token->content, "env") == 0)
			return (ft_env(bundle));
		else if (ft_strcmp(bundle->token->content, "pwd") == 0)
			return (ft_pwd(bundle));
		else if (ft_strcmp(bundle->token->content, "export") == 0)
			return (ft_export(bundle));
		else if (ft_strcmp(bundle->token->content, "unset") == 0)
			return (ft_unset(bundle));
		else if (ft_strcmp(bundle->token->content, "echo") == 0)
			return (ft_echo(bundle));
	}
	return (FAIL);
}

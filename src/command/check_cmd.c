/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:05 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/21 17:07:50 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *list_last(t_token *token)
{
	t_token *temp;

	if (token == NULL)
		return (NULL);
	temp = token;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

int is_bin(t_bundle *bundle)
{
	char *bin;
	char *cmd;
	char *bin_cmd;
	t_token *dup;

	bin = ft_strdup("/bin/");
	cmd = ft_strdup(bundle->token->content);
	bin_cmd = ft_strjoin(bin, cmd);

	dup = NULL;
	while (bundle->token->next && bundle->token->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
		if (dup == NULL)
			dup = bundle->token;
		else
			list_last(dup)->next = bundle->token;
	}


}

int is_builtin(t_bundle *bundle)
{
	if (bundle->token->back_space || bundle->token->next->token_type >= REDIR_IN)
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

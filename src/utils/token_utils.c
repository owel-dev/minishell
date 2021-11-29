/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:40:42 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/29 21:01:41 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir_token(t_token *token)
{
	return (token->token_type >= REDIR_IN && token->token_type <= D_REDIR_OUT);
}

int	is_io_token(t_token *token)
{
	return (token->token_type >= REDIR_IN);
}

char	*join_env_str(char *content, char *env, int start, int end)
{
	char	*pre;
	char	*new_content;

	if ((start - 2) > 0)
		pre = ft_substr(content, 0, start - 1);
	else
		pre = "";
	new_content = ft_strjoin(pre, env);
	free(env);
	return (new_content);
}

void	check_env_token(t_token *token, t_bundle *bundle)
{
	int		start;
	int		end;
	char	*new_content;
	char	*env;
	char	*temp;

	if (ft_strlen(token->content) < 2)
		return ;
	start = 1;
	while (token->content[start])
	{
		if (token->content[start - 1] == '$' && !is_space(token->content[start]))
		{
			end = start;
			while (token->content[end] && !is_space(token->content[end]))
				end++;
			temp = ft_substr(token->content, start, end - start);
			env = ft_getenv(bundle, temp);
			new_content = join_env_str(token->content, env, start, end);
			free(temp);
			start = ft_strlen(new_content);
			temp = ft_substr(token->content, end, ft_strlen(token->content));
			env = ft_strjoin(new_content, temp);
			free(new_content);
			free(temp);
			free(token->content);
			token->content = env;
		}
		start++;
	}
}

void	replace_env_token(t_token *temp, t_bundle *bundle)
{
	t_token	*delete_token;
	char	*env_tem;

	env_tem = ft_getenv(bundle, temp->content);
	free(temp->content);
	if (env_tem == NULL)
	{
		temp->pre->next = temp->next;
		delete_token = temp;
		temp = temp->pre;
		free(delete_token);
	}
	else
		temp->content = env_tem;
}

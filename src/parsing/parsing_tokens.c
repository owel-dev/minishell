/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 02:23:14 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/05 02:36:41 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_token(char *str, int start, int end, int token_type)
{
	char	*new_str;
	int		i;

	if (token_type == S_CLOSE || token_type == D_CLOSE)
	{
		start++;
		end--;
	}
	new_str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (start < end + 1)
	{
		new_str[i++] = str[start++];
	}
	new_str[i] = '\0';
	return (new_str);
}

int	get_token(t_token **token, char *cmd, int i, int start)
{
	int	quote;
	int	token_type;
	int	back_space;

	quote = 0;
	back_space = FALSE;
	while (cmd[i])
	{
		token_type = check_vaild_str(cmd, i);
		if (token_type > 0)
		{
			if (token_type == ENV)
				i = parsing_env_str(cmd, i);
			if (token_type == D_REDIR_IN || token_type == D_REDIR_OUT)
				i++;
			if (token_type == S_CLOSE || token_type == D_CLOSE)
				i = parsing_quote_str(cmd, i, token_type);
			break ;
		}
		i++;
	}
	if (cmd[i] && is_space(cmd[i + 1]))
		back_space = TRUE;
	ft_lstadd_back(token, ft_lstnew( \
	make_token(cmd, start, i, token_type), token_type, back_space));
	return (i);
}

int	parsing_token_list(t_bundle *bundle)
{
	int		i;
	int		start;
	char	*cmd;
	
	i = 0;
	cmd = bundle->cmd_line;
	start = 0;
	while (cmd[i])
	{
		while (cmd[i] && is_space(cmd[i]))
			i++;
		start = i;
		i = get_token(&bundle->token, cmd, i, start);
		i++;
	}
	t_token *temp;
	int size = ft_lstsize(bundle->token);
	temp = bundle->token;
	while (size--)
	{
		printf("%s %d %d\n", temp->content, temp->token_type, temp->back_space);
		bundle->token = temp->next;
		temp = bundle->token;
	}
	return (1);
}

int	parsing_token(t_bundle *bundles)
{
	int	i;

	i = 0;
	while (bundles[i].cmd_line)
	{
		bundles[i].quote = 0;
		parsing_token_list(&bundles[i]);
		i++;
	}
	return (0);
}

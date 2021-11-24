/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:37:09 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/24 17:54:27 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_iotoken(t_bundle *bundle)
{
	int	type;

	type = tokenlst_last(bundle->token)->token_type;
	if (type == PIPE)
	{
		bundle->pipe_token = NULL;
		return ;
	}
	if (bundle->pipe_token == NULL)
		bundle->pipe_token = tokenlst_last(bundle->token);
}

int	set_token_type(int token_type, t_bundle *bnde, int i)
{
	if (token_type == ENV)
		i = parsing_env_str(bnde->cmd_line, i); // env 토큰 문자열 길이 체크
	else if ((token_type == REDIR_IN || token_type == REDIR_OUT))
	{
		if (bnde->token == NULL)
			return (i);
		tokenlst_last(bnde->token)->redir = token_type;
	}
	else if (token_type == D_REDIR_IN || token_type == D_REDIR_OUT)
	{
		i++;
		if (bnde->token == NULL)
			return (i);
		tokenlst_last(bnde->token)->redir = token_type;
	}
	else if (token_type == S_CLOSE || token_type == D_CLOSE)
		i = parsing_quote_str(bnde->cmd_line, i, token_type); // quote 토큰 문자열 길이 체크
	else if (token_type == PIPE)
	{
		bnde->is_pipe = TRUE;
		if (bnde->pipe_token == NULL)
			return (i);
		bnde->pipe_token->pipe = PIPE;
	}
	return (i);
}

char	*make_token(char *str, int start, int end, int token_type)
{
	char	*new_str;
	int		i;

	if (token_type == S_CLOSE || token_type == D_CLOSE) //quote 문자 자르기
	{
		start++;
		end--;
	}
	else if (token_type == ENV)
		start++;
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

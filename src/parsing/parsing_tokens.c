/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 02:23:14 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/21 00:41:03 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_iotoken(t_bundle *bundle)
{
	int	type;

	type = ft_lstlast(bundle->token)->token_type;
	if (type == PIPE)
	{
		bundle->pipe_token = NULL;
		return ;
	}
	if (bundle->pipe_token == NULL)
		bundle->pipe_token = ft_lstlast(bundle->token);
}

int	set_token_type(int token_type, t_bundle *bnde, int i)
{
	if (token_type == ENV)
		i = parsing_env_str(bnde->cmd_line, i); // env 토큰 문자열 길이 체크
	else if ((token_type == REDIR_IN || token_type == REDIR_OUT))
		ft_lstlast(bnde->token)->redir = token_type;
	else if (token_type == D_REDIR_IN || token_type == D_REDIR_OUT)
	{
		ft_lstlast(bnde->token)->redir = token_type;
		i++;
	}
	else if (token_type == S_CLOSE || token_type == D_CLOSE)
		i = parsing_quote_str(bnde->cmd_line, i, token_type); // quote 토큰 문자열 길이 체크
	else if (token_type == PIPE)
	{
		bnde->pipe_token->pipe = token_type;
		bnde->is_pipe = TRUE;
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

int	get_token(t_bundle *bnde, int i, int start)
{
	int	token_type;
	int	back_space;

	bnde->quote = 0;
	back_space = FALSE;
	while (bnde->cmd_line[i])
	{
		token_type = check_vaild_str(bnde->cmd_line, i); // token type set
		if (token_type > 0)
		{
			i = set_token_type(token_type, bnde, i);
			break ;
		}
		i++;
	}
	if ((bnde->cmd_line[i] && is_space(bnde->cmd_line[i + 1])) || !bnde->cmd_line[i]) // 해당 토큰이 공백으로 종료되었는지 (quote의 공백없이 종료와 구분)
		back_space = TRUE;
	ft_lstadd_back(&bnde->token, ft_lstnew(make_token \
	(bnde->cmd_line, start, i, token_type), token_type, back_space)); // 토큰 생성 후 연결리스트에 추가
	return (i);
}

int	parsing_token_list(t_bundle *bundle)
{
	int		i;
	int		start;
	char	*cmd;

	i = 0;
	start = 0;
	while (bundle->cmd_line[i])
	{
		while (bundle->cmd_line[i] && is_space(bundle->cmd_line[i])) // 스페이스 제거
			i++;
		start = i;
		i = get_token(bundle, i, start); //token 문자열 생성 및 타입 지정
		set_iotoken(bundle);
		i++;
	}
	bundle->head = bundle->token;
	// t_token *temp;
	// int size = ft_lstsize(bundle->token);
	// int lok = 0;
	// temp = bundle->token;
	// while (lok < size)
	// {
	// 	printf("%s %d\n", temp->content, temp->token_type);
	// 	temp = temp->next;
	// 	lok++;
	// } // test 출력
	return (1);
}

int	parsing_token(t_bundle *bundles)
{
	int	i;

	i = 0;
	while (bundles[i].cmd_line)
	{
		bundles[i].quote = 0;
		parsing_token_list(&bundles[i]); //bundle 별 token 리스트 생성
		i++;
	}
	return (0);
}

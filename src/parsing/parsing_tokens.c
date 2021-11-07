/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 02:23:14 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/07 20:02:00 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_token(char *str, int start, int end, int token_type)
{
	char	*new_str;
	int		i;

	if (token_type == S_CLOSE || token_type == D_CLOSE) //quoto 문자 자르기
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

int	get_token(t_bundle *bnde, char *cmd, int i, int start)
{
	int	token_type;
	int	back_space;

	bnde->quote = 0;
	back_space = FALSE;
	while (cmd[i])
	{
		token_type = check_vaild_str(cmd, i); // token type set
		if (token_type > 0)
		{
			if (token_type == ENV)
				i = parsing_env_str(cmd, i); // env 토큰 문자열 길이 체크
			if (token_type == D_REDIR_IN || token_type == D_REDIR_OUT)
				i++;
			if (token_type == S_CLOSE || token_type == D_CLOSE)
				i = parsing_quote_str(cmd, i, token_type); // quote 토큰 문자열 길이 체크
			if (token_type == PIPE)
				bnde->is_pipe = TRUE;
			break ;
		}
		i++;
	}
	if (cmd[i] && is_space(cmd[i + 1])) // 해당 토큰이 공백으로 종료되었는지 (quote의 공백없이 종료와 구분)
		back_space = TRUE;
	ft_lstadd_back(&bnde->token, ft_lstnew( \
	make_token(cmd, start, i, token_type), token_type, back_space)); // 토큰 생성 후 연결리스트에 추가
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
		while (cmd[i] && is_space(cmd[i])) // 앞 스페이스 제거
			i++;
		start = i;
		i = get_token(bundle, cmd, i, start); //token 문자열 생성 및 타입 지정
		i++;
	}
	// t_token *temp;
	// int size = ft_lstsize(bundle->token);
	// temp = bundle->token;
	// while (size--)
	// {
	// 	printf("%s %d %d\n", temp->content, temp->token_type, bundle->is_pipe);
	// 	bundle->token = temp->next;
	// 	temp = bundle->token;
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

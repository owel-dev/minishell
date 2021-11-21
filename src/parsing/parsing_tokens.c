/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 02:23:14 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/21 16:57:50 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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


int	check_vaild_token_list(t_bundle *bundle)
{
	t_token *temp;
	int size;
	int error;

	temp = bundle->token;
	size = ft_lstsize(bundle->token);
	error = 0;
	while (temp)
	{
		if (is_redir_token(temp))
		{
			if (temp->next == NULL)
				error = printf("minishell: syntax error near unexpected token 'newline'\n");
			else if (temp->next->token_type >= REDIR_IN)
				error = printf("minishell: syntax error near unexpected token '%s'\n", temp->next->content);
		}
		else if (temp->token_type == PIPE && bundle->head == temp)
			error = printf("minishell: syntax error near unexpected token `|'\n");
		else if (temp->token_type == ENV)
			replace_env_token(temp, bundle);
		if (error)
			return (FAIL);
		temp = temp->next;
	}
	return (SUCCESS);
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
	if (check_vaild_token_list(bundle) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	parsing_token(t_bundle *bundles)
{
	int	i;

	i = 0;
	while (bundles[i].cmd_line)
	{
		bundles[i].quote = 0;
		if (parsing_token_list(&bundles[i]) == FAIL) //bundle 별 token 리스트 생성
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

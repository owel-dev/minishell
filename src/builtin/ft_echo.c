/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:54 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/03 20:35:25 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *append_buf(t_bundle *bundle, char *buf)
{
	char *ret;

	ret = ft_strjoin(buf, bundle->token->content);
	if (ret == NULL)
		return (NULL);
	if (bundle->token->next && bundle->token->back_space)
	{
		ret = ft_strjoin(ret, " ");
		if (ret == NULL)
			return (NULL);
	}
	return (ret);
}

int find_another(char *content, char *another)
{
	while (*content)
	{
		if (!ft_strchr(another, *content))
			return (1);
		content++;
	}
	return (0);
}

int	ft_echo(t_bundle *bundle)
{
	int n_option;
	int word;
	char *buf_output;

	n_option = 0;
	word = 0;
	buf_output = "";
	while (bundle->token->next && bundle->token->next->token_type != PIPE) //전체적으로 env 치환 기능 추가
	{
		bundle->token = bundle->token->next;
		if (!ft_strncmp(bundle->token->content, "-n", 2)&& \
			!find_another(bundle->token->content, "-ne") && \
			!word)
		{
			n_option = 1;
			continue ;
		}
		else
		{
			word = 1;
			buf_output = append_buf(bundle, buf_output);
			if (buf_output == NULL)
				return (FAIL);
		}
	}
	if (buf_output)
		write(1, buf_output, ft_strlen(buf_output));
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}

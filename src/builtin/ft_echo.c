/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:54 by hyospark          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/22 19:18:58 by ulee             ###   ########.fr       */
=======
/*   Updated: 2021/11/22 19:00:51 by ulee             ###   ########.fr       */
>>>>>>> d96a578e64dcc94f79aa84356b50f97f485a2d58
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

int	ft_echo(t_bundle *bundle)
{
	int n_option;
	char *buf_output;

	n_option = 0;
	buf_output = NULL;
	while (bundle->token->next && bundle->token->token_type != PIPE) //전체적으로 env 치환 기능 추가
	{
		bundle->token = bundle->token->next;
		if (ft_strncmp(bundle->token->content, "-n", 2) == 0) //strncmp 수정
		{
			n_option = 1;
			continue ;
		}
		if (is_redir_token(bundle->token))
			redir_handler(bundle);
		buf_output = append_buf(bundle, buf_output);
		if (buf_output == NULL)
			return (FAIL);
	}
	write(1, buf_output, ft_strlen(buf_output));
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:39:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/19 19:49:18 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int  ft_cd(t_token *token)
{
	int ret_chdir;
	char *dir;

	if (token->next != NULL)
	{
		printf("error\n");
		while (token != NULL || token->next->token_type != PIPE)
			token = token->next;
		return (FAIL);
	}
	if (token == NULL || token->next->token_type == PIPE)
		dir = "~";
	else
		dir = token->content;
	ret_chdir = chdir(dir);
	if (ret_chdir == -1)
	{
		printf("%s\n", strerror(errno));
		return (FAIL);
	}
	return (SUCCESS);
}

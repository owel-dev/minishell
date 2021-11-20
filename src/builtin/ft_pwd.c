/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:11 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/20 19:44:21 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_token *token)
{
	char	*ret_pwd;
	char	dir[1000];

	if (token != NULL)
	{
		while (token != NULL || token->next->token_type != PIPE)
			token = token->next;
	}
	ret_pwd = getcwd(dir, 1000);
	if (ret_pwd == 0)
	{
		printf("%s\n", strerror(errno));
		return (FAIL);
	}
	printf("%s\n", dir);
	return (SUCCESS);
}

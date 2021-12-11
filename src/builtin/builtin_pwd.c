/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:17:51 by ulee              #+#    #+#             */
/*   Updated: 2021/12/11 20:17:59 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_bundle *bundle)
{
	char	*ret_pwd;
	char	dir[1000];

	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
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

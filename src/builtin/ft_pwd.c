/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:11 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/21 14:17:01 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_bundle *bundle)
{
	char	*ret_pwd;
	char	dir[1000];

	while (bundle->token->next && bundle->token->token_type != PIPE)
	{
		//redirection
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

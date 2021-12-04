/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:54 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/04 04:09:13 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_bundle *bundle)
{
	int i = 0;
	if (bundle->env == NULL)
		return (FAIL);
	if (bundle->token->next && bundle->token->next->token_type < ENV)
	{
		printf("env: %s: No such file or directory\n", bundle->token->next->content);
		return (FAIL);
	}
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
	}
	while (bundle->env[i])
		printf("%s\n", (bundle->env)[i++]);
	return (SUCCESS);
}

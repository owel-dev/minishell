/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:54 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/20 14:29:30 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_bundle *bundle)
{
	int i = 0;
	if (bundle == NULL || bundle->env == NULL || bundle->token == NULL)
		return (FAIL);
	if (bundle->token->next == NULL || bundle->token->next->token_type == PIPE)
	{
		while (bundle->env[i])
			printf("%s\n", (bundle->env)[i++]);
		return (SUCCESS);
	}
	while (bundle->token && bundle->token->token_type != PIPE)
		bundle->token = bundle->token->next;
	return (FAIL);
}

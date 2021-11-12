/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:26:11 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/12 17:00:32 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_bundle *bundle)
{
	int result;
	char *content_first;
	char *content_second;

	result = 0;
	if (bundle->token->back_space == 1)
	{
		content_first = bundle->token->content;
		content_second = NULL;
		if (bundle->token->next != NULL)
			content_second = bundle->token->next->content;
		if (ft_strcmp(content_first, "cd") == 0)
		{
			if (content_second != NULL)
				ft_cd(content_second);
			else
				ft_cd("~");
		}
		else if (ft_strcmp(content_first, "env") == 0)
			ft_env(bundle->env);
		else if (ft_strcmp(content_first, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(content_first, "export") == 0)
			ft_export(content_second);
		else if (ft_strcmp(content_first, "unset") == 0)
			ft_unset(content_second);
	}
	return (result);
}

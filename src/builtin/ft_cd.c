/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:39:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/04 19:33:30 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int  ft_cd(t_bundle *bundle)
{
	int		ret_chdir;
	char	*dir;
	t_token	*next_token;
	char 	*home;

	next_token = bundle->token->next;
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
	}
	// if (next_token == NULL || is_io_token(next_token) || !ft_strcmp(next_token->content, "~"))
	// else
	dir = next_token->content;
	if (!ft_strncmp(dir, "~", 1))
	{
		home = NULL;
		home = ft_getenv(bundle, "HOME");
		dir = ft_strjoin(home, ++dir);
	}
	ret_chdir = chdir(dir);
	if (ret_chdir == -1)
	{
		printf("bash: cd: %s: %s\n", dir, strerror(errno));
		bundle->token = bundle->token->next;
		return (FAIL);
	}
	return (SUCCESS);
}

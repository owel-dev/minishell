/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:39:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/02 04:37:23 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int  ft_cd(t_bundle *bundle)
{
	int		ret_chdir;
	char	*dir;
	t_token	*next_token;

	next_token = bundle->token->next;
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
	}
	if (next_token == NULL || is_io_token(next_token) || !ft_strcmp(next_token->content, "~"))
		dir = ft_getenv(bundle, "HOME");
	else
		dir = next_token->content;
	ret_chdir = chdir(dir);
	if (ret_chdir == -1)
	{
		print_error(strerror(errno));
		return (FAIL);
	}
	return (SUCCESS);
}

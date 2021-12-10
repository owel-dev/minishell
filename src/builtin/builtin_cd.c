/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:39:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/08 15:19:02 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int  builtin_cd(t_bundle *bundle)
{
	int		ret_chdir;
	char	*dest_path;
	char 	*home_path;

	if (!bundle->token->next)
		dest_path = builtin_getenv(bundle, "HOME");
	else
		dest_path = ft_strdup(bundle->token->next->content);
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
		bundle->token = bundle->token->next;
	if (!ft_strncmp(dest_path, "~", 1))
	{
		home_path = builtin_getenv(bundle, "HOME");
		dest_path = ft_strjoin(home_path, ++dest_path);
		ft_free(home_path);
	}
	ret_chdir = chdir(dest_path);
	free(dest_path);
	if (ret_chdir == -1)
	{
		printf("bash: cd: %s: %s\n", dest_path, strerror(errno));
		bundle->token = bundle->token->next;
		return (FAIL);
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:05 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/02 20:14:24 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_bin(t_bundle *bundle)
{
	char **arr;
	char *path_env;
	char **paths;
	char *cmd;
	int i;
	int status;
	int path_len;

	arr = make_arr(make_list(bundle));
	cmd = ft_strdup(bundle->token->content);

	if (ft_strchr(cmd, '/'))
		return (exec_cmd(bundle, cmd, arr));
	else
	{
		path_env = ft_getenv(bundle, "PATH");
		paths = ft_split(path_env, ':');
		i = 0;
		path_len = ft_arrlen(paths);
		while (paths[i])
		{
			if (i == path_len - 1)
				status = other_cmd(bundle, paths[i++], cmd, arr, 1);
			else
				status = other_cmd(bundle, paths[i++], cmd, arr, 0);
			if (status == SUCCESS)
				return (SUCCESS);
		}
		return (FAIL);
	}
}

int is_builtin(t_bundle *bundle)
{
	if (!bundle->token->next || bundle->token->back_space || is_io_token(bundle->token->next))
	{
		if (ft_strcmp(bundle->token->content, "cd") == 0)
			return (ft_cd(bundle));
		else if (ft_strcmp(bundle->token->content, "env") == 0)
			return (ft_env(bundle));
		else if (ft_strcmp(bundle->token->content, "pwd") == 0)
			return (ft_pwd(bundle));
		else if (ft_strcmp(bundle->token->content, "export") == 0)
			return (ft_export(bundle));
		else if (ft_strcmp(bundle->token->content, "unset") == 0)
			return (ft_unset(bundle));
		else if (ft_strcmp(bundle->token->content, "echo") == 0)
			return (ft_echo(bundle));
		else if (ft_strcmp(bundle->token->content, "exit") == 0 && bundle->token == bundle->head)
			return (ft_exit(bundle));
	}
	return (FAIL);
}

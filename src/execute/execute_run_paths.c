/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_run_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:22:52 by ulee              #+#    #+#             */
/*   Updated: 2021/12/14 20:41:34 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**make_pathlist(void)
{
	char	*path_env;
	char	**path_list;

	path_env = builtin_getenv("PATH");
	path_list = ft_split(path_env, ':');
	ft_free(path_env);
	return (path_list);
}

char	*make_fullpath(char *path, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd);
	ft_free(temp);
	return (full_path);
}

int	print_not_found(t_bundle *bundle)
{
	printf("bash: %s: command not found\n", \
		bundle->token->content);
	g_global.status = 127;
	return (FAIL);
}

int	execute_run_paths(t_bundle *bundle, char *cmd, char **arg_arr)
{
	char	**path_list;
	int		i;
	char	*full_path;
	int		status;
	int		ret;

	path_list = make_pathlist();
	i = 0;
	while (path_list[i])
	{
		full_path = make_fullpath(path_list[i], cmd);
		status = run_cmd(full_path, arg_arr);
		ft_free(full_path);
		if (status == 256 || status == 3 || status == 0 || \
			status == 2)
		{
			ft_two_free(path_list);
			return (status);
		}
		i++;
	}
	ret = print_not_found(bundle);
	ft_two_free(path_list);
	return (ret);
}

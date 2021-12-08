/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:05 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/08 17:04:32 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *make_fullpath(char *path, char *cmd)
{
	char *temp;
	char *full_path;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

int exec_cmd(t_bundle *bundle, char *cmd, char **arr)
{
	int pid;
	int status;
	int exec_status;

	pid = fork();
	if (pid == -1)
		return (256);
	if (pid == 0)
	{
		exec_status = execve(cmd, arr, bundle->env);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (status);
}

void set_gloval_status(int status)
{
	if (status == 2)
		g_status = 130;
	else if (status == 3)
		g_status = 131;
}

int execute_bin(t_bundle *bundle)
{
	char **arg_arr;
	char *path_env;
	char **path_list;
	char *cmd;
	char *full_path;
	int i;
	int status;

	cmd = bundle->token->content;
	arg_arr = execute_make_arr(bundle);
	if (ft_strchr(cmd, '/'))
		return (exec_cmd(bundle, cmd, arg_arr));
	else
	{
		path_env = builtin_getenv(bundle, "PATH");
		path_list = ft_split(path_env, ':');
		ft_free(path_env);
		i = 0;
		while (path_list[i])
		{
			full_path = make_fullpath(path_list[i], cmd);
			status = exec_cmd(bundle, full_path, arg_arr);
			free(full_path);
			if (status == 2 || status == 3)
			{
				set_gloval_status(status);
				return (FAIL);
			}
			if (status == 0)
				return (SUCCESS);
			i++;
		}
		all_free(path_list);
		printf("bash: %s: command not found\n", cmd);
		g_status = 127;
		return (FAIL);
	}
}

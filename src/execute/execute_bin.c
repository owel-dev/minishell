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

int run_cmd(t_bundle *bundle, char *cmd, char **arr)
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

int execute_bin(t_bundle *bundle)
{
	char **arg_arr;
	char *cmd;
	int	ret;

	cmd = ft_strdup(bundle->token->content);
	arg_arr = execute_make_arr(bundle);
	if (ft_strchr(cmd, '/'))
		ret = run_cmd(bundle, cmd, arg_arr);
	else
		ret = execute_run_paths(bundle, cmd, arg_arr);
	ft_free(cmd);
	ft_two_free(arg_arr);
	return (ret);
}

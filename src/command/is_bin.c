/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:05 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/03 18:55:20 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int other_cmd(t_bundle *bundle, char *env_path, char *cmd, char **arr, int last_flag)
{
	int pid;
	char *full_path;
	int status;
	int exec_status;

	full_path = ft_strjoin(env_path, "/");
	full_path = ft_strjoin(full_path, cmd);
	pid = fork();
	if (pid == -1)
		return (FAIL);
	if (pid == 0)
	{
		exec_status = execve(full_path, arr, bundle->env);
		if (last_flag == 1)
			printf("bash: %s: command not found\n", cmd);
		exit(1);
	}
	waitpid(pid, &status, 0);
	// printf("print status: %d\n", status);
	if (status == 0)
		return (SUCCESS);
	if (status == 2 || status == 3)
	{
		// printf("%d\n", status);
		return (status);
	}
	return (FAIL);
}

int exec_cmd(t_bundle *bundle, char *cmd, char **arr)
{
	int pid;
	int status;
	int exec_status;

	pid = fork();
	if (pid == -1)
		return (FAIL);
	if (pid == 0)
	{
		exec_status = execve(cmd, arr, bundle->env);
		print_error(strerror(errno));
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (status == 256)
		return (FAIL);
	return (SUCCESS);
}


t_list *make_list(t_bundle *bundle)
{
	char *token_content;
	t_list *list;
	t_token *temp;

	list = NULL;
	temp = bundle->token;
	while (temp->next && temp->next->token_type != PIPE)
	{
		temp = temp->next;
		token_content = ft_strdup(temp->content);
		ft_lstadd_back(&list, ft_lstnew(token_content));
	}
	return (list);
}

char **make_arr(t_list *list)
{
	char **ret;
	int len;
	int i;

	len = ft_lstsize(list);
	ret = (char **)malloc(sizeof(char *) * (len + 2));
	if (ret == NULL)
		return (NULL);
	ret[len + 1] = NULL;
	ret[0] = " ";
	i = 1;
	while (i <= len)
	{
		ret[i++] = ft_strdup(list->content);
		list = list->next;
	}
	ft_lstclear(&list);
	return (ret);
}

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
			if (status == 256)
				return (127);
			else if (status == 2)
				return (130);
			else if (status == 3)
				return (131);
		}
		return (FAIL);
	}
}

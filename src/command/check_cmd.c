/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:05 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/28 18:40:16 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int other_cmd(t_bundle *bundle, char *env_path, char *cmd, char **arr)
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
		// printf("%s\n", strerror(errno));
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (status == 256)
		return (FAIL);
	return (SUCCESS);
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
		printf("%s\n", strerror(errno));
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

	arr = make_arr(make_list(bundle));
	cmd = ft_strdup(bundle->token->content);
	if (ft_strchr(cmd, '/'))
		return (exec_cmd(bundle, cmd, arr));
	else
	{
		path_env = ft_getenv(bundle, "PATH");
		paths = ft_split(path_env, ':');
		while (paths[i])
		{
			status = other_cmd(bundle, paths[i++], cmd, arr);
			if (status == SUCCESS)
				return (SUCCESS);
		}
	}
	exec_cmd(bundle, cmd, arr);
	return (SUCCESS);
}

int is_builtin(t_bundle *bundle)
{
	// if (!bundle->token->next || bundle->token->back_space || is_io_token(bundle->token->next))
	if (!bundle->token->next || bundle->token->back_space)
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
	}
	return (FAIL);
}

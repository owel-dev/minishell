/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:05 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/02 04:35:40 by hyospark         ###   ########.fr       */
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

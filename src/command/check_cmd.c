/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:05 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/22 20:55:39 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *list_last(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

int list_len(t_token *dup)
{
	int len;

	len = 0;
	while (dup)
	{
		len++;
		dup = dup->next;
	}
	return (len);
}

t_token *dup_token(t_token *token)
{
	t_token *ret;

	ret = malloc(sizeof(t_token));
	ret->pre = token->pre;
	ret->next = token->next;
	ret->pipe = token->pipe;
	ret->redir = token->redir;
	ret->fd[0] = token->fd[0];
	ret->fd[1] = token->fd[1];
	ret->content = token->content;
	ret->token_type = token->token_type;
	ret->back_space = token->back_space;

	return (ret);
}

char **list_to_arr(t_token *dup)
{
	char **ret;
	int len;
	int i;

	len = list_len(dup);
	ret = (char **)malloc(sizeof(char *) * (len + 2));
	if (ret == NULL)
		return (NULL);
	ret[len + 1] = NULL;
	ret[0] = " ";
	i = 1;
	while (i <= len)
	{
		ret[i] = ft_strdup(dup->content);
		i++;
		dup = dup->next;
	}
	return (ret);
}
int is_bin(t_bundle *bundle)
{
	char *cmd;
	char *bin_cmd;
	char **arr;
	t_token *dup;
	int	status;
	int pid;
	t_token *one;

	cmd = ft_strdup(bundle->token->content);
	bin_cmd = ft_strjoin("/bin/", cmd);
	if (bin_cmd == NULL)
		return (FAIL);
	free(cmd);
	dup = NULL;
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
		one = dup_token(bundle->token);
		one->next = NULL;
		if (dup == NULL)
			dup = one;
		else
			list_last(dup)->next = one;
	}
	pid = fork();
	if (pid < 0)
		return (FAIL);
	if (pid == 0)
	{
		arr = list_to_arr(dup);
		execve(bin_cmd, arr, bundle->env);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (SUCCESS);
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
	}
	return (FAIL);
}

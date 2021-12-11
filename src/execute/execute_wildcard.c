/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:23:46 by ulee              #+#    #+#             */
/*   Updated: 2021/12/11 20:25:50 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*get_list_file(void)
{
	DIR				*dir_ptr;
	struct dirent	*file;
	t_list			*files;

	dir_ptr = opendir(".");
	file = readdir(dir_ptr);
	files = NULL;
	while (file)
	{
		if (ft_strncmp(file->d_name, ".", 1) != 0)
			ft_lstadd_back(&files, ft_lstnew(ft_strdup(file->d_name)));
		file = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return (files);
}

t_list	*get_list_check(char *cmd)
{
	t_list	*checks;
	int		start;
	char	*word;
	int		i;

	checks = NULL;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '*')
		{
			ft_lstadd_back(&checks, ft_lstnew(ft_strdup("*")));
			while (cmd[i] && cmd[i] == '*')
				i++;
		}
		else
		{
			start = i;
			while (cmd[i] && cmd[i] != '*')
				i++;
			word = ft_substr(cmd, start, i - start);
			ft_lstadd_back(&checks, ft_lstnew(word));
		}
	}
	return (checks);
}

char	*check_valid(t_list *checks_dup, t_list *checks, char *files_dup)
{
	if (checks_dup == checks)
	{
		if (ft_strncmp(files_dup, checks_dup->content, \
			ft_strlen(checks_dup->content)) != 0)
			return (NULL);
		files_dup += ft_strlen(checks_dup->content);
		return (files_dup);
	}
	else if (checks_dup->next == NULL)
	{
		if (ft_strendstr(files_dup, checks_dup->content) == NULL)
			return (NULL);
		else if (*(ft_strendstr(files_dup, checks_dup->content) + 1) != '\0')
			return (NULL);
	}
	else
	{
		if (ft_strnstr(files_dup, checks_dup->content, \
			ft_strlen(files_dup)) == NULL)
			return (NULL);
		files_dup = ft_strendstr(files_dup, checks_dup->content) + 1;
		return (files_dup);
	}
	return (files_dup);
}

t_list	*get_list_needfile(t_list *files, t_list *checks)
{
	t_list	*checks_dup;
	char	*files_dup;
	t_list	*ret;

	ret = NULL;
	while (files)
	{
		checks_dup = checks;
		files_dup = files->content;
		while (checks_dup)
		{
			if (ft_strcmp(checks_dup->content, "*") != 0)
			{
				files_dup = check_valid(checks_dup, checks, files_dup);
				if (files_dup == NULL)
					break ;
			}
			checks_dup = checks_dup->next;
		}
		if (checks_dup == NULL)
			ft_lstadd_back(&ret, ft_lstnew(ft_strdup(files->content)));
		files = files->next;
	}
	return (ret);
}

t_list	*execute_wildcard(char *token_content)
{
	t_list	*files;
	t_list	*checks;
	t_list	*ret;

	files = get_list_file();
	checks = get_list_check(token_content);
	ret = get_list_needfile(files, checks);
	return (ret);
}

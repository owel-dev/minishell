#include "../minishell.h"

t_list *get_list_file(void)
{
	DIR *dir_ptr;
	struct dirent *file;
	t_list *files;

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

t_list *get_list_check(char *token_content)
{
	char *cmd;
	t_list *checks;
	int start;
	char *word;
	int i;

	cmd = token_content;
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

t_list *get_list_needfile(t_list *files, t_list *checks)
{
	t_list *checks_dup;
	char *files_dup;
	t_list *ret;

	checks_dup = NULL;
	files_dup = NULL;
	ret = NULL;
	while (files)
	{
		checks_dup = checks;
		files_dup = files->content;
		while (checks_dup)
		{
			if (ft_strcmp(checks_dup->content, "*") != 0)
			{
				if (checks_dup == checks)
				{
					if (ft_strncmp(files_dup, checks_dup->content, ft_strlen(checks_dup->content)) != 0)
						break;
					files_dup += ft_strlen(checks_dup->content);
				}
				else if (checks_dup->next == NULL)
				{
					if (ft_strendstr(files_dup, checks_dup->content) == NULL)
						break;
					else if (*(ft_strendstr(files_dup, checks_dup->content) + 1) != '\0')
						break;
				}
				else
				{
					if (ft_strnstr(files_dup, checks_dup->content, ft_strlen(files_dup)) == NULL)
						break;
					files_dup = ft_strendstr(files_dup, checks_dup->content) + 1;
				}
			}
			checks_dup = checks_dup->next;
		}
		if (checks_dup == NULL)
			ft_lstadd_back(&ret, ft_lstnew(ft_strdup(files->content)));
		files = files->next;
	}
	return (ret);
}

t_list *get_list_wildcard(char *token_content)
{
	t_list *files;
	t_list *checks;
	t_list *ret;

	chdir("/Users/ulee/minishell");
	files = get_list_file();
	checks = get_list_check(token_content);
	ret = get_list_needfile(files, checks);
	return (ret);
}

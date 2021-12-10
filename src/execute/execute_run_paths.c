#include "../minishell.h"

char **make_pathlist(t_bundle *bundle)
{
	char *path_env;
	char **path_list;

	path_env = builtin_getenv(bundle, "PATH");
	path_list = ft_split(path_env, ':');
	ft_free(path_env);
	return (path_list);
}

char *make_fullpath(char *path, char *cmd)
{
	char *temp;
	char *full_path;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

int set_status(int status)
{
	if (status == 0)
		return (SUCCESS);
	else if (status == 2)
		g_status = 130;
	else if (status == 3)
		g_status = 131;
	return (FAIL);
}

int		print_not_found(t_bundle *bundle)
{
	printf("bash: %s: command not found\n", \
		bundle->token->content);
	g_status = 127;
	return (FAIL);
}

int execute_run_paths(t_bundle *bundle, char *cmd, char **arg_arr)
{
	char **path_list;
	int i;
	char *full_path;
	int status;
	int ret;

	path_list = make_pathlist(bundle);
	i = 0;
	while (path_list[i])
	{
		full_path = make_fullpath(path_list[i], cmd);
		status = run_cmd(bundle, full_path, arg_arr);
		ft_free(full_path);
		if (status == 2 || status == 3 || status == 0)
		{
			ret = set_status(status);
			ft_two_free(path_list);
			return (ret);
		}
		i++;
	}
	ret = print_not_found(bundle);
	ft_two_free(path_list);
	return (ret);
}

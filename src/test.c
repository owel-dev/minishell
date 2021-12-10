/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:30:10 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/10 16:27:53 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **start_sh(char **env, char *input)
{
	t_bundle	*bundles;
	int			i;
	int			result;
	char		**return_env;

	if (is_space_str(input))
		return (NULL);
	bundles = split_bundle(env, input);
	if (parsing_token(bundles) == FAIL)
	{
		free_bundle(bundles);
		return (NULL);
	}
	i = 0;
	while (bundles[i].cmd_line)
	{
		result = execute_cmd(&bundles[i]);
		i++;
		if (bundles[i].cmd_line != NULL && \
			(result == SUCCESS && bundles[i].priority == P_OR) \
			|| (result == FAIL && bundles[i].priority == P_AND))
		{
			i++;
		}
	}
	return_env = dup_envp(env);
	// ft_two_free(env);
	free_bundle(bundles);
	return (return_env);
}

char	**dup_envp(char **envp)
{
	char	**env;
	int		len;
	int		i;

	len = 0;
	while (envp[len])
		len++;
	env = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int ft_isallblank(char *str)
{
	if (!ft_strcmp(str, ""))
		return (1);
	while (*str)
	{
		if (!is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

void	loop(char **env, char **av)
{
	char	*input;
	char 	**dup_env;
	char 	**temp;
	int i;

	dup_env = env;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	i = 1;
	while(av[i])
	{
		input = ft_strdup(av[i]);
		// if (input == NULL)
		// {
		// 	printf("logout\n");
		// 	exit(0);
		// }
		// if (ft_isallblank(input))
		// {
		// 	free(input);
		// 	continue;
		// }
		add_history(input);
		temp = dup_env;
		dup_env = start_sh(dup_env, input);
		// ft_two_free(temp);
		// free(input);
		i++;
	}
}

int main(int argc, char **av, char **env)
{
	char **dup_env;
	char **dup_av;

	g_status = 0;
	dup_env = dup_envp(env);
	dup_av = dup_envp(av);
	loop(dup_env, dup_av);
	return 0;
}

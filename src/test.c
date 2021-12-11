/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:30:10 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/11 15:09:55 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_sh(char ***env, char *input)
{
	t_bundle	*bundles;
	int			i;
	int			result;
	char		**use_env;

	use_env = *env;
	if (is_space_str(input))
		return ;
	bundles = split_bundle(use_env, input);
	if (parsing_token(bundles) == FAIL)
	{
		free_bundle(bundles);
		return ;
	}
	i = 0;
	while (bundles[i].cmd_line)
	{
		result = execute_cmd(&bundles[i++]);
		if (bundles[i].cmd_line != NULL && \
			(result == SUCCESS && bundles[i].priority == P_OR) \
			|| (result == FAIL && bundles[i].priority == P_AND))
			i++;
	}
	*env = bundles->env;
	free_bundle(bundles);
}

void	loop(char **env, char **av)
{
	char	*input;
	char 	**env_dup;
	char 	**temp;

	env_dup = dup_env(env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	int i = 1;
	while(av[i])
	{
		input = ft_strdup(av[i]);
		if (input == NULL)
		{
			printf("logout\n");
			exit(0);
		}
		if (ft_isallblank(input))
		{
			free(input);
			continue;
		}
		add_history(input);
		start_sh(&env_dup, input);
		free(input);
		i++;
	}
	ft_two_free(env_dup);
}

int main(int argc, char **av, char **env)
{
	char **dup_env;
	char **dup_av;

	loop(env, av);
	return 0;
}

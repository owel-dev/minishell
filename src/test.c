/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:26:02 by ulee              #+#    #+#             */
/*   Updated: 2021/12/14 20:41:28 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_main(int argc, char **av, char **env)
{
	(void)argc;
	(void)av;
	g_global.env = dup_env(env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	start_sh(char *input)
{
	t_bundle	*bundles;
	int			i;
	int			result;

	if (is_space_str(input))
		return ;
	bundles = split_bundle(input);
	if (parsing_token(bundles) == FAIL)
	{
		free_bundle(bundles);
		return ;
	}
	i = 0;
	while (bundles[i].cmd_line)
	{
		result = execute_cmd(&bundles[i++]);
		if (((bundles[i].cmd_line != NULL) && (result == SUCCESS && bundles[i].priority == P_OR)) || (result == FAIL && bundles[i].priority == P_AND))
			i++;
	}
	free_bundle(bundles);
}

int	main(int argc, char **av, char **env)
{
	char	*input;

	init_main(argc, av, env);
	int i = 1;
	while (av[i])
	{
		input = ft_strdup(av[i]);
		if (input == NULL)
		{
			printf("logout\n");
			exit(0);
		}
		if (ft_isallblank(input))
		{
			ft_free(input);
			continue ;
		}
		add_history(input);
		start_sh(input);
		ft_free(input);
		i++;
	}
	ft_two_free(g_global.env);
	return (0);
}

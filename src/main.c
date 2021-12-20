/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:26:02 by ulee              #+#    #+#             */
/*   Updated: 2021/12/21 05:27:06 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_priority(t_bundle *bundle, int result, int level, int flag)
{
	if (flag)
	{
		return (bundle->cmd_line != NULL && ((result == SUCCESS \
				&& bundle->priority == P_OR) || (result == FAIL && \
				bundle->priority == P_AND)));
	}
	return (bundle->cmd_line != NULL && (bundle->priority_level > level \
			|| (result == SUCCESS && bundle->priority == P_OR) || \
			(result == FAIL && bundle->priority == P_AND)));
}

void	start_sh(char *input)
{
	t_bundle	*bundles;
	int			i;
	int			result;
	int			level;

	if (is_space_str(input))
		return ;
	bundles = split_bundle(input);
	if (parsing_token(bundles) == FAIL)
		return (free_bundle(bundles));
	i = 0;
	level = 0;
	while (bundles[i].cmd_line)
	{
		result = execute_cmd(&bundles[i++]);
		level = bundles[i - 1].priority_level;
		if (return_priority(&bundles[i], result, level, 1))
		{
			i++;
			while (return_priority(&bundles[i], result, level, 0))
				i++;
		}
	}
	free_bundle(bundles);
}

int	main(int argc, char **av, char **env)
{
	char	*input;

	init_main(argc, av, env);
	while (TRUE)
	{
		set_signal();
		signal(SIGUSR1, init_signal);
		kill(0, SIGUSR1);
		signal(SIGUSR1, unset_signal);
		input = readline("minishell$ ");
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		if (!ft_isallblank(input))
		{
			add_history(input);
			start_sh(input);
		}
		ft_free(input);
	}
	ft_two_free(g_global.env);
	return (0);
}

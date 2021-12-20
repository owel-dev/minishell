/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:02:54 by ulee              #+#    #+#             */
/*   Updated: 2021/12/21 05:31:38 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	unset_signal(int signum)
{
	if (signum == SIGUSR1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	init_signal(int signum)
{
	if (signum == SIGUSR1)
		return ;
}

void	init_main(int argc, char **av, char **env)
{
	(void)argc;
	(void)av;
	g_global.env = dup_env(env);
}

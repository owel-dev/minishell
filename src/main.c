/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:30:10 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/02 03:43:35 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_sh(char **env, char *input)
{
	t_bundle	*bundles;
	int			i;
	// int			result;

	if (is_space_str(input))
		return ;
	bundles = split_bundle(env, input);
	// split_token(bundle);
	i = 0;
	// while (bundles[i].commands)
	// {
	// 	result = excute_cmd();
	// 	if ((result == TRUE && bundles[i].priority == P_OR) \
	// 	|| (result == FALSE && bundles[i].priority == P_AND))
	// 	{
	// 		i++;
	// 	}
	// 	i++;
	// }
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

void	loop(char **env)
{
	char	*input;

	while(TRUE)
	{
		input = readline("minishell$ ");
		add_history(input);
		start_sh(env, input);
		free(input);
	}
}

int main(int argc, char const *argv[], char **envp)
{
	// signal(SIGINT, SIG_IGN);
	loop(dup_envp(envp));//env 복제해서 매개변수로 넘긴다.
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:11:46 by ulee              #+#    #+#             */
/*   Updated: 2021/11/12 11:11:47 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int ac, char **av, char **env)
{
	// char *str;
	char s[100];
	// while (1)
	// {
    	// pwd();
		// scanf("%s", s);
		// printf("%shh\n", s);
		// cd(str);
	// }

	g_env = dup_two(env);
	if (g_env == NULL)
		return (1);

	// ft_export("USER=main");
	// ft_env(g_env);

	// int i = 0;
	// while (g_env[i])
	// {
	// 	printf("%s\n", g_env[i]);
	// 	i++;
	// }

	// signal(SIGINT, (void *)sig_handler);

	// while (1)
	// {
    // 	ft_pwd();
	// 	scanf("%s", s);
	// 	ft_cd(s);
	// 		printf("%s\n", s);
	// }

	// char *key;

	// key = ft_split("ulee=hello", '$')[0];
	// printf("%s", key);

	// char *str = getenv("USE2R");
	// printf("%s", str);

	ft_unset("USER");
	ft_env(g_env);
    return 0;
}

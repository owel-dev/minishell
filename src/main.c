/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:30:10 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/19 20:04:30 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_sh(char **env, char *input)
{
	t_bundle	*bundles;
	int			i;
	int			result;

	if (is_space_str(input)) // check space input
		return ;
	bundles = split_bundle(env, input); //별개의 명령어별 bundle 생성 및 우선순위 setting
	parsing_token(bundles); // bundle 별 cmd 연결리스트 parsing
	i = 0;
	while (bundles[i].cmd_line) // 우선순위체크 및 cmd 실행
	{
		result = execute_cmd(&bundles[i]);
		if (result < 0)
			child_exit(bundles);
		if ((result == TRUE && bundles[i].priority == P_OR) \
		|| (result == FALSE && bundles[i].priority == P_AND))
		{
			i++;
		}
		i++;
	}
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

void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("%c[K\n", 27);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		printf("zsh: quit           %s", "a.out");
		rl_replace_line("               ", 0);
		rl_redisplay();
		printf("%c\n", 27);
		exit(0);
	}
}

void	loop(char **env)
{
	char	*input;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
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
	loop(dup_envp(envp));
	return 0;
}

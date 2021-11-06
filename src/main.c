/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:30:10 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/06 21:46:17 by hyospark         ###   ########.fr       */
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
	bundles = split_bundle(env, input);//별개의 명령어별 bundle 생성 및 우선순위 setting
	parsing_token(bundles); // bundle 별 cmd 연결리스트 parsing
	i = 0;
	while (bundles[i].cmd_line) // 우선순위체크 및 cmd 실행
	{
		result = execute_cmd(&bundles[i]);
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
	loop(dup_envp(envp));//env 복제본을 매개변수로 넘긴다.
	return 0;
}

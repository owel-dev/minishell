/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:30:02 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/04 13:23:03 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_cmd(t_bundle *bundle)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	if (pipe(fd) < 0)
		print_error_exit("pipe function error", EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		print_error_exit("pipe fork error", EXIT_FAILURE);
	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		return (1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		while(bundle->token->next)
		{
			bundle->token = bundle->token->next;
			if (bundle->token->pre->token_type == PIPE)
				break ;
		}
		waitpid(pid ,&status, 0);
		return (0);
	}
}

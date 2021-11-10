/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:30:02 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/10 12:22:57 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_handler(t_bundle *bundle)
{
	int	pid;
	int	status;
	int	fd[2];

	if (pipe(fd) < 0)
		print_error("PIPE_ERROR\n");
	pid = fork();
	if (pid < 0)
		print_error("FORK_ERROR\n");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[0], STDIN_FILENO);
	}
	else
	{
		close(fd[1]);
		dup2(fd[1], STDOUT_FILENO);
		wait(&status);
	}
}

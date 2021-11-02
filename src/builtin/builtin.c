/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:26:11 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/01 22:21:07 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execve_builtIn()
{
	char	*builtIn[] = {"/bin/ls", NULL};
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		execve("/bin/ls", builtIn, NULL);
	}
	else
		wait(&pid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:35:44 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/12 15:08:59 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_cmd()
{
	
}

int	execute_cmd(t_bundle *bundle)
{
	int result;

	result = 0;
	if (bundle->is_pipe == TRUE)
		result = pipe_cmd();
	// else
		// 파이프 없는 기본 cmd
	return (result);
}

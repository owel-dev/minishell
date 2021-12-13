/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 01:47:17 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/13 19:03:58 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_bundle(t_bundle *bundles)
{
	int	i;

	i = 0;
	while (bundles[i].cmd_line != NULL)
	{
		free(bundles[i].cmd_line);
		if (bundles[i].head)
			tokenlst_clear(bundles[i].head);
		i++;
	}
	free(bundles);
}

void	child_exit(t_bundle *bundles, int status)
{
	int	i;

	i = 0;
	free(bundles->input);
	while (bundles[i].cmd_line)
	{
		free(bundles[i].cmd_line);
		if (bundles[i].head)
			tokenlst_clear(bundles[i].head);
		i++;
	}
	free(bundles);
	exit(status);
}

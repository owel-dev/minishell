/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 01:47:17 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/15 16:02:01 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_bundle(t_bundle *bundles)
{
	int	i;

	i = 0;
	while (bundles[i].cmd_line != NULL)
	{
		ft_free(bundles[i].cmd_line);
		if (bundles[i].head)
			tokenlst_clear(bundles[i].head);
		i++;
	}
	ft_free(bundles);
}

void	child_exit(t_bundle *bundles, int status)
{
	int	i;

	i = 0;
	ft_free(bundles->input);
	while (bundles[i].cmd_line)
	{
		ft_free(bundles[i].cmd_line);
		if (bundles[i].head)
			tokenlst_clear(bundles[i].head);
		i++;
	}
	ft_free(bundles);
	exit(status);
}

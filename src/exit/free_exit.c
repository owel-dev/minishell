/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 01:47:17 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/19 16:38:50 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	free_bundle(t_bundle *bundles, int i)
{
	while (i >= 0)
	{
		if (bundles[i].cmd_line)
		{
			free(bundles[i].cmd_line);
			ft_lstclear(&bundles[i].head);
		}
		i--;
	}
	free(bundles);
}

void	child_exit(t_bundle *bundles, char *input)
{
	int	i;

	i = 0;
	while (bundles[i].cmd_line)
	{
		free(bundles[i].cmd_line);
		ft_lstclear(&bundles[i].head);
		i++;
	}
	free(input);
	exit(1);
}
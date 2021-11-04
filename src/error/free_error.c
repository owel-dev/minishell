/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 01:47:17 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/03 02:11:44 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	free_bundle(t_bundle *bundles, int i)
{
	while (i >= 0)
	{
		free(bundles[i].cmd_line);
		ft_lstclear(&bundles[i].token);
		i--;
	}
	free(bundles);
}

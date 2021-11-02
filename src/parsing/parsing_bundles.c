/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bundles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:58:22 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/02 16:06:26 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	set_bundle_line(t_bundle *bundle, int word_len)
{
	int		i;

	i = 0;
	bundle->cmd_line = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!bundle->cmd_line)
		return (1);
	return (0);
}

void	set_bundle(t_bundle *bundle, char **env, int bundles_num)
{
	int		i;

	i = 0;
	while (i < bundles_num)
	{
		bundle[i].env = env;
		bundle[i].is_quote = 0;
		bundle[i].priority = 0;
		i++;
	}
	bundle[bundles_num].cmd_line = NULL;
}

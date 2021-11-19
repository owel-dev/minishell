/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bundles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:58:22 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/19 17:19:38 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	set_bundle_line(t_bundle *bundle, int word_len)
{
	int		i;
	char	*tem;

	i = 0;
	tem = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!tem)
		return (1);
	bundle->cmd_line = tem;
	return (0);
}

void	set_bundle(t_bundle *bundle, char **env, int bundles_num, char *str)
{
	int		i;

	i = 0;
	while (i < bundles_num)
	{
		bundle[i].env = env;
		bundle[i].quote = 0;
		bundle[i].priority = 0;
		bundle[i].token = NULL;
		bundle[i].pipe_token = NULL;
		bundle[i].input = str;
		i++;
	}
}

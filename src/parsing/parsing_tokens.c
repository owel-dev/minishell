/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 02:23:14 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/01 22:29:50 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(char *str)
{
	char	**space;
	int		i;

	space = ft_split(str, ' ');
	if (space == NULL)
		print_error("SPACE_SPLIT_ERROR");
	i = 0;
	while (space[i])
		printf("%s\n", space[i++]);
}

void	split_command(char *str)
{
	char	**semi;
	int		i;

	semi = ft_split(str, ';');
	if (semi == NULL)
		print_error("SEMI_SPLIT_ERROR");
	i = 0;
	while(semi[i])
		parsing(semi[i++]);
}

char	**split_token(char const *s, char c)
{
	
}

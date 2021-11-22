/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:23:10 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/22 20:18:22 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_fdnum(char *str, int back)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	if (str == NULL)
		return (0);
	if (back && str[i] == '&')
	{
		fd = 2;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (fd);
}

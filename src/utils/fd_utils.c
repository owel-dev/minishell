/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:23:10 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/11 17:48:45 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_fdnum(char *str, int back)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (back && str[i] == '&')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	return (i);
}

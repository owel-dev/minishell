/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:39:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/17 16:39:16 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(char *path)
{
	int ret;

	if (path == NULL)
		return ;
	ret = chdir(path);
	if (ret == -1)
		printf("%s\n", strerror(errno));
}


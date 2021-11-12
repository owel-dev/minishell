/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:18:54 by ulee              #+#    #+#             */
/*   Updated: 2021/11/12 14:38:02 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_pwd(void)
{
	char *ret;
	char s[1000];

	ret = getcwd(s,1000);
	if (ret == 0)
	{
		printf("%s\n", strerror(errno));
		return ;
	}
	printf("%s\n", ret);
}

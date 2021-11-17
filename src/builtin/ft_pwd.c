/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:11 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/17 16:38:13 by hyospark         ###   ########.fr       */
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

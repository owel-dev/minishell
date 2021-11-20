/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:11 by hyospark          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/20 16:42:26 by ulee             ###   ########.fr       */
=======
/*   Updated: 2021/11/20 18:01:32 by hyospark         ###   ########.fr       */
>>>>>>> 91343758094c7f38930cb446a0dafab1370b70cc
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
int ft_pwd(t_bundle *bundle)
=======
int	ft_pwd(t_token *token)
>>>>>>> 91343758094c7f38930cb446a0dafab1370b70cc
{
	char	*ret_pwd;
	char	dir[1000];

<<<<<<< HEAD
	while (bundle->token && bundle->token->token_type != PIPE)
		bundle->token = bundle->token->next;
	ret_pwd = getcwd(dir,1000);
=======
	if (token != NULL)
	{
		while (token != NULL || token->next->token_type != PIPE)
			token = token->next;
	}
	ret_pwd = getcwd(dir, 1000);
>>>>>>> 91343758094c7f38930cb446a0dafab1370b70cc
	if (ret_pwd == 0)
	{
		printf("%s\n", strerror(errno));
		return (FAIL);
	}
	printf("%s\n", dir);
	return (SUCCESS);
}

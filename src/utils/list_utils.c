/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 00:31:12 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/19 19:56:01 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstnew(char *content, int token_type, int back_space)
{
	t_token	*new;

	if (content == NULL)
		return (NULL);
	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->token_type = token_type;
	new->back_space = back_space;
	new->redir = 0;
	new->pipe = 0;
	new->next = 0;
	return (new);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

void	ft_lstclear(t_token **lst)
{
	t_token	*temp;

	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(lst);
		lst = NULL;
		*lst = temp;
	}
	*lst = NULL;
}

int	ft_lstsize(t_token *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

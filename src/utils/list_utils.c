/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 00:31:12 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/09 18:20:00 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*tokenlst_new(char *content, int token_type, int back_space)
{
	t_token	*new_token;

	if (content == NULL)
		return (NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->content = content;
	new_token->pre = NULL;
	new_token->token_type = token_type;
	new_token->back_space = back_space;
	new_token->redir = 0;
	new_token->fd[0] = -2;
	new_token->fd[1] = -2;
	new_token->pipe = 0;
	new_token->next = NULL;
	return (new_token);
}

void	tokenlst_delete(t_token *lst)
{
	if (lst->pre && lst->next)
	{
		lst->pre->next = lst->next;
		lst->next->pre = lst->pre;
	}
	else if (lst->pre)
	{
		lst->pre->next = NULL;
	}
	else if (lst->next)
	{
		lst->next->pre = NULL;
	}
	free(lst->content);
	free(lst);
}

void	tokenlst_add_back(t_token **lst, t_token *new_token)
{
	t_token	*last;

	if (lst == NULL || new_token == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_token;
		return ;
	}
	last = tokenlst_last(*lst);
	new_token->pre = last;
	last->next = new_token;
}

void	tokenlst_clear(t_token *lst)
{
	t_token	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst->content);
		free(lst);
		lst = temp;
	}
}

int	tokenlst_size(t_token *lst)
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

t_token	*tokenlst_last(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

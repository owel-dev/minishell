#include "../minishell.h"


t_list *make_list(t_bundle *bundle)
{
	char *token_content;
	t_list *list;

	list = NULL;
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
		token_content = ft_strdup(bundle->token->content);
		if (ft_strchr(token_content, '*') != NULL)
			ft_lstadd_back(&list, execute_wildcard(token_content));
		else
			ft_lstadd_back(&list, ft_lstnew(token_content));
	}
	return (list);
}

char **make_arr(t_list *list)
{
	char **ret;
	int len;
	int i;
	t_list *temp;

	len = ft_lstsize(list);
	ret = (char **)malloc(sizeof(char *) * (len + 2));
	if (ret == NULL)
		return (NULL);
	ret[len + 1] = NULL;
	ret[0] = ft_strdup("");
	i = 1;
	temp = list;
	while (i <= len)
	{
		ret[i++] = ft_strdup(temp->content);
		temp = temp->next;
	}
	return (ret);
}

char **execute_make_arr(t_bundle *bundle)
{
	char **arg_arr;
	t_list *arg_list;

	arg_list = make_list(bundle);
	arg_arr = make_arr(arg_list);
	ft_lstclear(&arg_list);
	return (arg_arr);
}

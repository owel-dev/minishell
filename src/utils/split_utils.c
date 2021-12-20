/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:28:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/21 05:19:15 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sh_count_word(char const *s, int i, int count, int quote)
{
	if (ft_strlen(s) < 3)
		return (1);
	while (s[i])
	{
		if (is_quote(s[i], quote) > 0)
		{
			quote = is_quote(s[i], quote);
			if (quote != S_OPEN || quote != D_OPEN)
				quote = 0;
		}
		if (quote == 0 && check_priority(s, i) > 0)
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	sh_remove_paren(t_bundle *bundle, char const *s, int j, int word_len)
{
	int		flag;
	int		temp;

	temp = word_len;
	flag = 0;
	bundle->quote = 0;
	while (bundle->parenth && temp)
	{
		if (is_quote(s[j - temp], bundle->quote) > 0)
			bundle->quote = is_quote(s[j - temp], bundle->quote);
		if (bundle->quote == S_CLOSE || bundle->quote == D_CLOSE)
			bundle->quote = 0;
		if (!bundle->quote && (s[j - temp] == '(' \
		|| s[j - temp] == ')'))
			flag++;
		temp--;
	}
	bundle->cmd_line = (char *)malloc(sizeof(char) * (word_len + 1 - flag));
	if (!bundle->cmd_line)
		return (1);
	return (0);
}

int	sh_make_word(t_bundle *bundle, char const *s, int *j, int word_len)
{
	int		i;
	int		index;

	index = *j;
	i = 0;
	bundle->quote = 0;
	while (word_len)
	{
		if (bundle->parenth && !bundle->quote && \
		(s[index - word_len] == '(' || s[index - word_len] == ')'))
		{
			word_len--;
			continue ;
		}
		if (is_quote(s[index - word_len], bundle->quote) > 0)
			bundle->quote = is_quote(s[index - word_len], bundle->quote);
		if (bundle->quote == S_CLOSE || bundle->quote == D_CLOSE)
			bundle->quote = 0;
		bundle->cmd_line[i++] = s[index - word_len--];
	}
	bundle->cmd_line[i] = '\0';
	return (0);
}

int	cut_cmd(t_bundle *bundles, char const *s, int i, int j)
{
	int	word_len;
	int	par_level;

	word_len = 0;
	par_level = 0;
	while (s[j])
	{
		cut_priority(bundles, s, i, &j);
		bundles[i].priority_level = par_level;
		while (s[j] && !(!bundles[i].quote && check_priority(s, j)))
		{
			set_parent_level(&bundles[i], s[j], &par_level);
			set_bundle_quote(&bundles[i], s, j);
			j++;
			word_len++;
		}
		if (sh_remove_paren(&bundles[i], s, j, word_len))
			return (i);
		word_len = sh_make_word(&bundles[i], s, &j, word_len);
		if (word_len)
			return (i);
		i++;
	}
	return (-1);
}

t_bundle	*split_bundle(char const *str)
{
	int			bundles_num;
	t_bundle	*bundles;
	int			i;
	int			par_check;

	bundles_num = sh_count_word(str, 1, 1, 0);
	bundles = (t_bundle *)malloc(sizeof(t_bundle) * (bundles_num + 1));
	if (bundles == NULL)
		return (NULL);
	ft_bzero(bundles, sizeof(t_bundle) * (bundles_num + 1));
	bundles[bundles_num].cmd_line = NULL;
	par_check = check_parenth_bundle(str);
	set_bundle(bundles, bundles_num, str, par_check);
	i = cut_cmd(bundles, str, 0, 0);
	if (i > -1)
		free_bundle(bundles);
	return (bundles);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bundles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:58:22 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/21 05:04:05 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_bundle(t_bundle *bundle, int bundles_num, char const *str, int par)
{
	int		i;

	i = 0;
	while (i <= bundles_num)
	{
		bundle[i].input = (char *)str;
		bundle[i].parenth = par;
		bundle[i].priority_level = 0;
		i++;
	}
}

void	set_bundle_quote(t_bundle *bundles, char const *s, int j)
{
	bundles->quote = is_quote(s[j], bundles->quote);
	if (bundles->quote != S_OPEN && bundles->quote != D_OPEN)
		bundles->quote = 0;
}

int	check_parenth_bundle(char const *s)
{
	int	i;
	int	par_check;
	int	flag;

	par_check = 0;
	i = 0;
	flag = 0;
	while (s[i])
	{
		par_check += check_paren(s[i], par_check);
		if (par_check)
			flag = 1;
		i++;
	}
	if (par_check == 0 && flag)
		return (1);
	return (0);
}

int	set_parent_level(t_bundle *bundles, char s, int *par_level)
{
	int	check;

	if (!bundles->parenth)
		return (0);
	check = check_paren(s, *par_level);
	if (check == 1)
	{
		*par_level += 1;
	}
	else if (check < 0)
	{
		*par_level -= 1;
		return (1);
	}
	bundles->priority_level = *par_level;
	return (0);
}

void	cut_priority(t_bundle *bundles, char const *s, int i, int *j)
{
	int	index;

	index = *j;
	if (!is_quote(s[index], bundles[i].quote) && check_priority(s, index))
	{
		bundles[i].priority = check_priority(s, index);
		*j += 2;
	}
}

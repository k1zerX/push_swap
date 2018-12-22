/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:41:15 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/02 10:32:09 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		split_len(char const *s, char c)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] != c)
		{
			k++;
			while (s[i] && s[i] != c)
				i++;
			i--;
		}
		i++;
	}
	return (k);
}

static int		split_find(char const *s, char c, int *i, int *prev)
{
	while (s[*i] == c)
		(*i)++;
	*prev = *i;
	return (1);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		k;
	int		prev;
	char	**res;

	res = (char **)malloc(sizeof(*res) * (split_len(s, c) + 1));
	i = 0;
	k = 0;
	if (s && res)
	{
		split_find(s, c, &i, &prev);
		i--;
		while (s[++i])
			if (s[i] == c)
			{
				if (i - prev > 0)
					res[k++] = ft_strsub(s, prev, i - prev);
				if (split_find(s, c, &i, &prev) && s[i] == 0)
					i--;
			}
		if (i - prev > 0)
			res[k++] = ft_strsub(s, prev, i - prev);
		res[k] = 0;
	}
	return (res);
}

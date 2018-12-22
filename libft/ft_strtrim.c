/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:30:14 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/02 10:34:50 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		from;
	int		len;
	char	*res;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	from = -1;
	while (++from < len)
		if (s[from] != ' ' & s[from] != '\n' & s[from] != '\t')
			break ;
	i = len;
	while (--i > from)
		if (s[i] != ' ' & s[i] != '\n' & s[i] != '\t')
			break ;
	len = i - from + 1;
	res = ft_strnew(len);
	i = -1;
	if (res)
		while (++i < len)
			res[i] = s[from + i];
	return (res);
}

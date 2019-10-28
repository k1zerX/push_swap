/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:53:29 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 22:03:26 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "push_swap.h"
#include "libft.h"

void	ft_exit(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

t_nbr	*new_nbr(int n)
{
	t_nbr			*nbr;

	if (!(nbr = malloc(sizeof(t_nbr))))
		ft_exit();
	nbr->n = (unsigned int)n + ((unsigned int)1 << (sizeof(int) * 8 - 1));
	return (nbr);
}

int		cool_atoi(char **str)
{
	int		n;
	int		buf;
	char	sign;

	if (**str == '+')
		++(*str);
	if (**str == '-')
	{
		sign = -1;
		++(*str);
	}
	else
		sign = 1;
	if (!ft_isdigit(**str))
		ft_exit();
	n = 0;
	while (ft_isdigit(**str))
	{
		buf = n;
		n = n * 10 + (**str - '0') * sign;
		if ((sign == -1 && n > buf) || (sign == 1 && n < buf))
			ft_exit();
		++(*str);
	}
	return (n);
}

void	fill_list_str(t_ps_list *list, char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) || *str == '-' || *str == '+')
			list_add(list, new_nbr(cool_atoi(&str)));
		else if (ft_isspace(*str))
			++str;
		else if (*str)
			ft_exit();
	}
}

void	fill_list(t_ps_list *list, int ac, char *av[])
{
	while (ac > 1)
	{
		fill_list_str(list, *++av);
		--ac;
	}
}

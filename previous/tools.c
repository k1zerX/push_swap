/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 09:38:56 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/21 13:38:04 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "libft.h"

void	ft_exit(char status)
{
	if (status == ERROR)
		exit(1);
}

void	fill_stack_1(t_ps_stack *a, char *str)
{
	int		buf;
	char	b;

	b = 0;
	while (ft_isspace(*str))
		str++;
	if (ft_isdigit(*str))
	{
		b = 1;
		buf = *str - '0';
		while (ft_isdigit(*++str))
			buf = buf * 10 + *str - '0';
	}
	if (ft_isspace(*str))
	{
		fill_stack_1(a, str);
	}
	else if (*str)
		ft_exit(ERROR);
	if (b)
		ft_stack_push(a, ft_new_elem(&buf, sizeof(buf), 1));
}

void	fill_stack(t_ps_stack *a, int ac, char **av)
{
	--ac;
	fill_stack_1(a, av[ac]);
	if (ac > 1)
		fill_stack(a, ac, av);
}

char	is_sorted(t_ps_stack *a)
{
	t_ps_elem	*tmp;
	int			buf;

	tmp = a->start;
	buf = *(int *)tmp->content;
	while (tmp)
	{
		if (buf > *(int *)tmp->content)
			return (0);
		buf = *(int *)tmp->content;
		tmp = tmp->next;
	}
	return (1);
}

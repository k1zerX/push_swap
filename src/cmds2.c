/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:37:52 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/21 13:06:37 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		ra(t_stack *a, t_stack *b)
{
	t_elem	*tmp;
	t_elem	*buf;

	(void)b;
	buf = ft_stack_pop(a);
	tmp = a->start;
	if (!tmp)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = buf;
	a->len++;
	return (1);
}

int		rb(t_stack *a, t_stack *b)
{
	t_elem	*tmp;
	t_elem	*buf;

	(void)a;
	buf = ft_stack_pop(b);
	tmp = b->start;
	if (!tmp)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = buf;
	b->len++;
	return (1);
}

int		rr(t_stack *a, t_stack *b)
{
	ra(a, b);
	rb(a, b);
	return (1);
}

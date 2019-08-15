/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:43:04 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/21 13:07:54 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		rra(t_stack *a, t_stack *b)
{
	t_elem	*tmp;
	t_elem	*buf;

	(void)b;
	tmp = a->start;
	if (!tmp)
		return (0);
	if (!tmp->next)
	{
		sa(a, b);
		return (1);
	}
	while (tmp->next->next)
		tmp = tmp->next;
	buf = tmp->next;
	tmp->next = NULL;
	a->len--;
	ft_stack_push(a, buf);
	return (1);
}

int		rrb(t_stack *a, t_stack *b)
{
	t_elem	*tmp;
	t_elem	*buf;

	(void)a;
	tmp = b->start;
	if (!tmp)
		return (0);
	if (!tmp->next)
	{
		sb(a, b);
		return (1);
	}
	while (tmp->next)
		tmp = tmp->next;
	buf = tmp->next;
	tmp->next = NULL;
	b->len--;
	ft_stack_push(b, buf);
	return (1);
}

int		rrr(t_stack *a, t_stack *b)
{
	rra(a, b);
	rrb(a, b);
	return (1);
}

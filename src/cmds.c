/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:22:58 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/21 13:14:41 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		sa(t_stack *a, t_stack *b)
{
	t_elem	*t0;
	t_elem	*t1;

	(void)b;
	if (!(t0 = ft_stack_pop(a)))
		return (0);
	if (!(t1 = ft_stack_pop(a)))
		return (0);
	ft_stack_push(a, t0);
	ft_stack_push(a, t1);
	return (1);
}

int		sb(t_stack *a, t_stack *b)
{
	t_elem	*t0;
	t_elem	*t1;

	(void)a;
	if (!(t0 = ft_stack_pop(b)))
		return (0);
	if (!(t1 = ft_stack_pop(b)))
		return (0);
	ft_stack_push(b, t0);
	ft_stack_push(b, t1);
	return (1);
}

int		ss(t_stack *a, t_stack *b)
{
	sa(a, b);
	sb(a, b);
	return (1);
}

int		pa(t_stack *a, t_stack *b)
{
	t_elem		*tmp;

	(void)b;
	tmp = ft_stack_pop(a);
	if (!tmp)
		return (0);
	ft_stack_push(a, tmp);
	return (1);
}

int		pb(t_stack *a, t_stack *b)
{
	t_elem		*tmp;

	(void)a;
	tmp = ft_stack_pop(b);
	if (!tmp)
		return (0);
	ft_stack_push(b, tmp);
	return (1);
}

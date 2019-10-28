/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:44:52 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:44:53 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "ps_stack.h"

char	check_pa(t_ps_stack *a, t_ps_stack *b)
{
	(void)a;
	if (!b->top)
		return (0);
	return (1);
}

int		pa(t_ps_stack *a, t_ps_stack *b)
{
	t_ps_selem	*tmp;

	tmp = b->top;
	b->top = tmp->next;
	if (b->top)
		b->top->prev = NULL;
	else
		b->bot = NULL;
	tmp->next = a->top;
	if (a->top)
		a->top->prev = tmp;
	else
		a->bot = tmp;
	a->top = tmp;
	--b->len;
	++a->len;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:44:48 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:44:49 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "ps_stack.h"

char	check_pb(t_ps_stack *a, t_ps_stack *b)
{
	(void)b;
	if (!a->top)
		return (0);
	return (1);
}

int		pb(t_ps_stack *a, t_ps_stack *b)
{
	t_ps_selem	*tmp;

	tmp = a->top;
	a->top = tmp->next;
	if (a->top)
		a->top->prev = NULL;
	else
		a->bot = NULL;
	tmp->next = b->top;
	if (b->top)
		b->top->prev = tmp;
	else
		b->bot = tmp;
	b->top = tmp;
	--a->len;
	++b->len;
	return (1);
}

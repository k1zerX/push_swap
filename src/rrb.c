/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:44:36 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:44:38 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "ps_stack.h"

char	check_rrb(t_ps_stack *a, t_ps_stack *b)
{
	(void)a;
	if (b->top && b->top->next)
		return (1);
	return (0);
}

int		rrb(t_ps_stack *a, t_ps_stack *b)
{
	(void)a;
	b->bot->next = b->top;
	b->top->prev = b->bot;
	b->top = b->bot;
	b->bot = b->bot->prev;
	b->bot->next = NULL;
	b->top->prev = NULL;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:44:39 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:44:40 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "ps_stack.h"

char	check_rra(t_ps_stack *a, t_ps_stack *b)
{
	(void)b;
	if (a->top && a->top->next)
		return (1);
	return (0);
}

int		rra(t_ps_stack *a, t_ps_stack *b)
{
	(void)b;
	a->bot->next = a->top;
	a->top->prev = a->bot;
	a->top = a->bot;
	a->bot = a->bot->prev;
	a->bot->next = NULL;
	a->top->prev = NULL;
	return (1);
}

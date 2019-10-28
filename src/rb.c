/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:44:43 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:45:09 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "ps_stack.h"

char	check_rb(t_ps_stack *a, t_ps_stack *b)
{
	(void)a;
	if (b->top && b->top->next)
		return (1);
	return (0);
}

int		rb(t_ps_stack *a, t_ps_stack *b)
{
	(void)a;
	b->top->prev = b->bot;
	b->bot->next = b->top;
	b->bot = b->top;
	b->top = b->top->next;
	b->top->prev = NULL;
	b->bot->next = NULL;
	return (1);
}

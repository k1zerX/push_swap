/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:44:55 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:44:56 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "ps_stack.h"

char	check_sb(t_ps_stack *a, t_ps_stack *b)
{
	(void)a;
	if (b->top && b->top->next)
		return (1);
	return (0);
}

int		sb(t_ps_stack *a, t_ps_stack *b)
{
	t_ps_selem	*tmp1;
	t_ps_selem	*tmp2;
	t_ps_selem	*tmp3;

	(void)a;
	tmp1 = b->top;
	tmp2 = tmp1->next;
	tmp3 = tmp2->next;
	tmp1->prev = tmp2;
	tmp1->next = tmp3;
	tmp2->prev = NULL;
	tmp2->next = tmp1;
	if (tmp3)
		tmp3->prev = tmp1;
	b->top = tmp2;
	return (1);
}

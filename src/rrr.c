/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:44:35 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:44:36 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "ps_stack.h"

char	check_rrr(t_ps_stack *a, t_ps_stack *b)
{
	return (check_rra(a, b) && check_rrb(a, b));
}

int		rrr(t_ps_stack *a, t_ps_stack *b)
{
	rra(a, b);
	rrb(a, b);
	return (1);
}

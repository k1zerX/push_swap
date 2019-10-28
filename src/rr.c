/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:44:41 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:44:42 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "ps_stack.h"

char	check_rr(t_ps_stack *a, t_ps_stack *b)
{
	return (check_ra(a, b) && check_rb(a, b));
}

int		rr(t_ps_stack *a, t_ps_stack *b)
{
	ra(a, b);
	rb(a, b);
	return (1);
}

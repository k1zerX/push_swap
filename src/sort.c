/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:48:01 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 22:00:44 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include "tools.h"
#include "libft.h"

void	do_cmd(t_state *state, t_cmds cmd)
{
	(*g_cmds[cmd].func)(&state->a, &state->b);
	ps_sol_add(&state->sol, cmd);
}

void	shift_a(t_state *state, unsigned int ra, unsigned int rra)
{
	if (ra < rra)
		while (ra > 0)
		{
			do_cmd(state, RA);
			--ra;
		}
	else
		while (rra > 0)
		{
			do_cmd(state, RRA);
			--rra;
		}
}

void	shift_b(t_state *state, unsigned int rb, unsigned int rrb)
{
	if (rb < rrb)
		while (rb > 0)
		{
			do_cmd(state, RB);
			--rb;
		}
	else
		while (rrb > 0)
		{
			do_cmd(state, RRB);
			--rrb;
		}
}

void	count_one(t_state *state, t_pos *i, const unsigned int n)
{
	t_ps_selem			*tmp;
	t_ps_selem			*next;
	unsigned int		len;

	i->ra = 0;
	len = 0;
	tmp = state->a.top;
	next = tmp->next;
	while (next)
	{
		++len;
		if (tmp->n < n && n < next->n)
			i->ra = len;
		tmp = next;
		next = next->next;
	}
	next = state->a.top;
	if (tmp->n > n && n > next->n)
		i->ra = len;
	++len;
	i->rra = len - i->ra;
}

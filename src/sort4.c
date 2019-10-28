/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:57:04 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 21:59:27 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include "tools.h"
#include "libft.h"

void	find_min(t_pos *i, t_pos *min_pos, unsigned int *min, unsigned int buf)
{
	buf = FT_MAX(i->ra, i->rb);
	if (buf < *min)
	{
		*min = buf;
		*min_pos = *i;
	}
	buf = FT_MAX(i->rra, i->rrb);
	if (buf < *min)
	{
		*min = buf;
		*min_pos = *i;
	}
	buf = i->ra + i->rrb;
	if (buf < *min)
	{
		*min = buf;
		*min_pos = *i;
	}
	buf = i->rra + i->rb;
	if (buf < *min)
	{
		*min = buf;
		*min_pos = *i;
	}
}

void	do_cmd_cycle(t_state *state, t_cmds cmd, unsigned int count)
{
	while (count > 0)
	{
		do_cmd(state, cmd);
		--count;
	}
}

void	shift(t_state *state, t_pos *i, unsigned int min)
{
	unsigned int	buf;

	if (FT_MAX(i->ra, i->rb) == min)
	{
		do_cmd_cycle(state, RA, i->ra);
		do_cmd_cycle(state, RB, i->rb);
	}
	else if (FT_MAX(i->rra, i->rrb) == min)
	{
		do_cmd_cycle(state, RRA, i->rra);
		do_cmd_cycle(state, RRB, i->rrb);
	}
	else if (i->ra + i->rrb == min)
	{
		do_cmd_cycle(state, RA, i->ra);
		do_cmd_cycle(state, RRB, i->rrb);
	}
	else if (i->rra + i->rb == min)
	{
		do_cmd_cycle(state, RRA, i->rra);
		do_cmd_cycle(state, RB, i->rb);
	}
}

void	solve_one(t_state *state)
{
	t_ps_selem			*tmp;
	t_pos				i;
	t_pos				min_pos;
	unsigned int		min;

	min = -1;
	i.rb = 0;
	i.rrb = state->b.len;
	tmp = state->b.top;
	while (tmp)
	{
		count_one(state, &i, tmp->n);
		find_min(&i, &min_pos, &min, 0);
		++i.rb;
		--i.rrb;
		tmp = tmp->next;
	}
	shift(state, &min_pos, min);
	do_cmd(state, PA);
}

void	to_norm(t_state *state)
{
	unsigned int	i;
	unsigned int	len;
	t_ps_selem		*tmp;

	i = 0;
	len = 0;
	tmp = state->a.top;
	while (tmp->n != 0)
	{
		++i;
		++len;
		tmp = tmp->next;
	}
	while (tmp)
	{
		++len;
		tmp = tmp->next;
	}
	shift_a(state, i, len - i);
}

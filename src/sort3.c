/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:56:37 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 21:58:38 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include "tools.h"
#include "libft.h"

void			sort_three_a(t_state *state)
{
	if (state->a.top->next->n > state->a.top->next->next->n && \
			state->a.top->next->n > state->a.top->n)
		do_cmd(state, RRA);
	else if (state->a.top->n > state->a.top->next->n && \
			state->a.top->n > state->a.top->next->next->n)
		do_cmd(state, RA);
	if (state->a.top->next->next->n > state->a.top->n && \
			state->a.top->n > state->a.top->next->n)
		do_cmd(state, SA);
}

void			sort_three_b(t_state *state)
{
	if (state->b.top->next->n < state->b.top->next->next->n && \
			state->b.top->next->n < state->b.top->n)
		do_cmd(state, RRB);
	else if (state->b.top->n < state->b.top->next->n && \
			state->b.top->n < state->b.top->next->next->n)
		do_cmd(state, RB);
	if (state->b.top->next->next->n < state->b.top->n && \
			state->b.top->n < state->b.top->next->n)
		do_cmd(state, SB);
	solve_one(state);
	solve_one(state);
	solve_one(state);
}

void			opti_sort(t_state *state)
{
	if (state->b.len == 3)
		sort_three_b(state);
	else
		while (state->b.len > 0)
			solve_one(state);
}

unsigned int	get_add_number(unsigned int len)
{
	return ((len > 10) ? (1) : (0));
}

void			sort(t_state *state)
{
	const unsigned int	max = state->a.len - 1;
	const unsigned int	number = MIN_NUMBER + get_add_number(state->a.len);
	const unsigned int	step = max / (number - 1);
	unsigned int		i;

	i = number + ((max % (number - 1)) ? (1) : (0));
	while (state->a.len > i)
		if (state->a.top->n % step && state->a.top->n != max)
			do_cmd(state, PB);
		else
			do_cmd(state, RA);
	while (state->a.len > MIN_NUMBER)
		if (state->a.top->n == 0 || state->a.top->n == max)
			do_cmd(state, RA);
		else
			do_cmd(state, PB);
	while (--i >= MIN_NUMBER)
		solve_one(state);
	opti_sort(state);
	to_norm(state);
}

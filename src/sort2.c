/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:55:56 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 21:58:17 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include "tools.h"
#include "libft.h"

t_sol_elem	*merge_gg_sqr(t_sol_elem *tmp, \
		unsigned int cmds[LEN], t_sol_elem *end)
{
	t_cmds		i;
	t_sol_elem	*prev;
	t_sol_elem	*next;

	i = RA;
	while (i < LEN)
	{
		if (cmds[i] > 0)
		{
			tmp->cmd = i;
			prev = tmp;
			tmp = tmp->next;
			--cmds[i];
		}
		else
			++i;
	}
	while (tmp != end)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	return (prev);
}

void		merge_gg(t_sol_elem *start, t_sol *sol)
{
	unsigned int	cmds[LEN];
	t_sol_elem		*tmp;
	t_sol_elem		*end;
	unsigned int	min;

	ft_bzero(cmds, sizeof(unsigned int) * LEN);
	tmp = start;
	while (tmp && (tmp->cmd == RA || tmp->cmd == RB || \
			tmp->cmd == RRA || tmp->cmd == RRB))
	{
		++cmds[tmp->cmd];
		tmp = tmp->next;
	}
	end = tmp;
	min = FT_MIN(cmds[RA], cmds[RB]);
	cmds[RA] -= min;
	cmds[RB] -= min;
	sol->len -= min;
	cmds[RR] += min;
	min = FT_MIN(cmds[RRA], cmds[RRB]);
	cmds[RRA] -= min;
	cmds[RRB] -= min;
	cmds[RRR] += min;
	sol->len -= min;
	merge_gg_sqr(start, cmds, end)->next = end;
}

void		merge(t_sol *sol)
{
	t_sol_elem	*tmp;

	if ((tmp = sol->top))
		while (tmp->next)
		{
			if (tmp->next->cmd == RA || tmp->next->cmd == RB || \
					tmp->next->cmd == RRA || tmp->next->cmd == RRB)
				merge_gg(tmp->next, sol);
			tmp = tmp->next;
		}
}

void		treatment_sol_cycle(t_sol *sol, t_sol_elem *a, \
				t_sol_elem *b, t_sol_elem *c)
{
	while (c)
	{
		if (g_cmds[b->cmd].func == g_cmds[c->cmd].cancel)
		{
			a->next = c->next;
			sol->len -= 2;
			free(b);
			free(c);
			if (sol->len < 2)
				return ;
			b = a->next;
			c = b->next;
		}
		else
		{
			a = b;
			b = c;
			c = c->next;
		}
	}
	merge(sol);
}

void		treatment_sol(t_sol *sol)
{
	t_sol_elem	*a;
	t_sol_elem	*b;
	t_sol_elem	*c;

	if (sol->len < 2)
		return ;
	a = sol->top;
	b = a->next;
	c = b->next;
	while (g_cmds[a->cmd].func == g_cmds[b->cmd].cancel)
	{
		sol->len -= 2;
		sol->top = c;
		free(a);
		free(b);
		if (sol->len < 2)
			return ;
		a = c;
		b = a->next;
		c = b->next;
	}
	treatment_sol_cycle(sol, a, b, c);
}

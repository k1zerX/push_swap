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

void	find_min(t_pos *i, t_pos *min_pos, unsigned int *min)
{
	unsigned int	buf;

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
		find_min(&i, &min_pos, &min);
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

void	sort(t_state *state, unsigned int len)
{
	const unsigned int	max = len - 1;
	const unsigned int	number = MIN_NUMBER + ADD_NUMBER;
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
	len -= i;
	while (--i >= MIN_NUMBER)
		solve_one(state);
	i = -1;
	while (++i <  len)
		solve_one(state);
	to_norm(state);
}

void	merge(t_sol *sol)
{
	t_sol_elem		*tmp;
	t_sol_elem		*start;
	t_sol_elem		*buf;
	t_sol_elem		*next;
	t_sol_elem		*prev;
	unsigned int	cmds[LEN];
	unsigned int	min;

	cmds[RA] = 0;
	cmds[RB] = 0;
	cmds[RRA] = 0;
	cmds[RRB] = 0;
	start = NULL;
	tmp = sol->top;
	while (tmp)
	{
		if (tmp->cmd == RA || tmp->cmd == RB || \
				tmp->cmd == RRA || tmp->cmd == RRB)
		{
			if (start == NULL)
				start = tmp;
			++cmds[tmp->cmd];
		}
		else if (start != NULL)
		{
			min = FT_MIN(cmds[RA], cmds[RB]);
			cmds[RA] -= min;
			cmds[RB] -= min;
			sol->len -= min;
			while (min > 0)
			{
				start->cmd = RR;
				prev = start;
				start = start->next;
				--min;
			}
			min = FT_MIN(cmds[RRA], cmds[RRB]);
			cmds[RRA] -= min;
			cmds[RRB] -= min;
			sol->len -= min;
			while (min > 0)
			{
				start->cmd = RRR;
				prev = start;
				start = start->next;
				--min;
			}
			while (cmds[RA] > 0)
			{
				start->cmd = RA;
				prev = start;
				start = start->next;
				--cmds[RA];
			}
			while (cmds[RB] > 0)
			{
				start->cmd = RB;
				prev = start;
				start = start->next;
				--cmds[RB];
			}
			while (cmds[RRA] > 0)
			{
				start->cmd = RRA;
				prev = start;
				start = start->next;
				--cmds[RRA];
			}
			while (cmds[RRB] > 0)
			{
				start->cmd = RRB;
				prev = start;
				start = start->next;
				--cmds[RRB];
			}
			buf = start;
			while (buf != tmp)
			{
				next = buf->next;
				free(buf);
				buf = next;
			}
			prev->next = tmp;
			start = NULL;
		}
		tmp = tmp->next;
	}
}

void	treatment_sol(t_sol *sol)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:30:18 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/14 00:26:36 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "ps_stack.h"
#include "ps_queue.h"
#include "cmds.h"
#include "gvars.h"
#include "radix_sort.h"
#include "avl.h"
#include "libft.h"


#include <stdio.h> //
void	print_node(t_node *node)
{
	printf("%d\n", node->priority);
}

void	print_list(t_ps_list list)
{
	t_ps_lelem	*tmp;

	tmp = list.start;
	printf("|------------------------|\n");
	printf("| len %d \t\t |\n", list.len);
	while (tmp)
	{
		printf("|\t %u\t%u\t |\n", tmp->nbr->pos + 1, tmp->nbr->n);
		tmp = tmp->next;
	}
	printf("|------------------------|\n");
}

void	print_arr(t_nbr **arr, int len)
{
	int		i;

	i = 0;
	while (i < len - 1)
	{
		printf("%d, ", arr[i]->n);
		++i;
	}
	printf("%d\n", arr[i]->n);
}

int		stack_len(t_ps_stack stack)
{
	t_ps_selem	*tmp;
	int			len;

	len = 0;
	tmp = stack.top;
	while (tmp)
	{
		++len;
		tmp = tmp->next;
	}
	return (len);
}

void	print_stacks(t_ps_stack a, t_ps_stack b)
{
	t_ps_selem				*tmp_a;
	t_ps_selem				*tmp_b;
	int						len_a;
	int						len_b;
	static unsigned int		count = 0;

	if (count)
	{
		printf("\n");
		printf("     ------ || ------     \n");
		printf("  --------  ||  --------  \n");
		printf("     ------ \\/ -----     \n");
		printf("\n");
	}
	len_a = stack_len(a);
	len_b = stack_len(b);
	tmp_a = a.top;
	tmp_b = b.top;
	printf("|------------------------|\n");
	while (len_a > len_b)
	{
		printf("|%4d : %-4d             |\n", tmp_a->start, tmp_a->end);
		--len_a;
		tmp_a = tmp_a->next;
	}
	while (len_b > len_a)
	{
		printf("|             %4d : %-4d|\n", tmp_b->start, tmp_b->end);
		--len_b;
		tmp_b = tmp_b->next;
	}
	while (len_b || len_a)
	{
		printf("|%4d : %-4d  %4d : %-4d|\n", tmp_a->start, tmp_a->end, tmp_b->start, tmp_b->end);
		--len_b;
		tmp_b = tmp_b->next;
		--len_a;
		tmp_a = tmp_a->next;
	}
	printf("| ---------    --------- |\n");
	printf("|     a            b     |\n");
	printf("|------------------------|\n");
	++count;
}
//
int		ft_cmp(int a, int b)
{
	return (a - b);
}

void	print_sol(t_sol sol)
{
	t_sol_elem	*tmp;

	tmp = sol.top;
	while (tmp)
	{
		write(1, g_cmds[tmp->cmd].name, g_cmds[tmp->cmd].len);
		tmp = tmp->next;
	}
}

void	ps_sol_add(t_sol *sol, t_cmds cmd)
{
	t_sol_elem	*tmp;

	if (!(tmp = malloc(sizeof(t_sol_elem))))
		ft_exit();
	tmp->next = NULL;
	if (sol->bot)
		sol->bot->next = tmp;
	else
		sol->top = tmp;
	sol->bot = tmp;
//	++sol->len;
}

void	do_cmd(t_state *state, t_cmds cmd)
{
	(*g_cmds[cmd].func)(&state->a, &state->b);
	ps_sol_add(&state->sol, cmd);
}

unsigned int	get_add_number(unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i * i <= len)
		++i;
	--i;
	return ((i > MIN_NUMBER) ? (i - MIN_NUMBER) : (0));
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
	buf = i->rra + i->rb;
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
	buf = FT_MAX(i->rra, i->rrb);
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
	else if (i->rra + i->rb == min)
	{
		do_cmd_cycle(state, RRA, i->rra);
		do_cmd_cycle(state, RB, i->rb);
	}
	else if (i->ra + i->rrb == min)
	{
		do_cmd_cycle(state, RA, i->ra);
		do_cmd_cycle(state, RRB, i->rrb);
	}
	else if (FT_MAX(i->rra, i->rrb) == min)
	{
		do_cmd_cycle(state, RRA, i->rra);
		do_cmd_cycle(state, RRB, i->rrb);
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
	const unsigned int	add_number = get_add_number(len);
	const unsigned int	number = MIN_NUMBER + add_number;
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

int		main(int ac, char *av[])
{
	t_state		state;
	t_ps_list	list;
	t_nbr		**arr;
	int			sum;
	int			len;

	sum = 0;
	len = 0;
	state = (t_state){(t_ps_stack){NULL, NULL, 0}, \
			(t_ps_stack){NULL, NULL, 0}, (t_sol){NULL, 0}};
	list = (t_ps_list){NULL, NULL, 0};
	fill_list(&list, ac, av);
	arr = get_arr(list);
	radix_sort(arr, list.len);
	fill_stack(&state.a, list, &sum, &len);
	print_stacks(state.a, state.b); //
	sort(&state, len);
	print_stacks(state.a, state.b); //
	treatment_sol(&state.sol);
	print_sol(state.sol);
	return (0);
}

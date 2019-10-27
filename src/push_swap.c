/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:30:18 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/27 23:24:31 by kbatz            ###   ########.fr       */
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


#include <stdio.h>
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

int		ft_cmp(int a, int b)
{
	return (a - b);
}

int		heuristic(t_state state)
{
	return (state.a.len + state.b.len + state.sol.len);
}

void	print_sol(t_sol sol)
{
	t_sol_elem	*tmp;

	tmp = sol.top;
	while (tmp)
	{
		printf("%s\n", g_cmds[tmp->cmd].name);//
		tmp = tmp->next;
	}
}

t_node		*new_node(int priority)
{
	t_node	*tmp;

	if (!(tmp = malloc(sizeof(t_node))))
		ft_exit();
	tmp->priority = priority;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->q = (t_ps_queue){NULL, NULL};
	return (tmp);
}

t_ps_stack	clone_stack(t_ps_stack cpy)
{
	t_ps_selem	*tmp;
	t_ps_selem	*buf;
	t_ps_selem	*prev;
	t_ps_stack	stack;

	if ((tmp = cpy.top))
	{
		if (!(buf = malloc(sizeof(t_ps_selem))))
			ft_exit();
		buf->prev = NULL;
		buf->start = tmp->start;
		buf->end = tmp->end;
		stack.top = buf;
		tmp = tmp->next;
		while (tmp)
		{
			prev = buf;
			if (!(buf = malloc(sizeof(t_ps_selem))))
				ft_exit();
			buf->prev = prev;
			buf->start = tmp->start;
			buf->end = tmp->end;
			prev->next = buf;
			tmp = tmp->next;
		}
		buf->next = NULL;
		stack.bot = buf;
		stack.len = cpy.len;
	}
	else
		stack = (t_ps_stack){NULL, NULL, 0};
	return (stack);
}

t_state	clone_state(t_state state)
{
	t_state		new_state;

	new_state.a = clone_stack(state.a);
	new_state.b = clone_stack(state.b);
//	new_state.sol = ;
	new_state.sol = (t_sol){NULL, state.sol.len};
	return (new_state);
}

void	treatment_a(t_ps_stack *a)
{
	t_ps_selem	*tmp;
	t_ps_selem	*next;

//	printf("before\n");
	if ((tmp = a->top))
	{
		next = tmp->next;
		while (next)
		{
//			printf("%p\n", tmp);
			next = tmp->next;
			if (next->start - tmp->end == 1)
			{
//			printf("%d:%d %d:%d\n", tmp->start, tmp->end, next->start, next->end);
				tmp->end = next->end;
				tmp->next = next->next;
				if (tmp->next == NULL)
					a->bot = tmp;
				--a->len;
				free(next);
			}
			else
				tmp = next;
			next = tmp->next;
		}
	}
//	printf("after\n");
}

void	treatment_b(t_ps_stack *b)
{
	t_ps_selem	*tmp;
	t_ps_selem	*next;

//	printf("before\n");
	if ((tmp = b->top))
	{
		next = tmp->next;
		while (next)
		{
//			printf("%p\n", tmp);
			next = tmp->next;
			if (tmp->start - next->end == 1)
			{
				tmp->start = next->start;
				tmp->next = next->next;
				if (tmp->next == NULL)
					b->bot = tmp;
				--b->len;
				free(next);
			}
			else
				tmp = next;
			next = tmp->next;
		}
	}
//	printf("after\n");
}

void	treatment(t_state *state)
{
	treatment_a(&state->a);
	treatment_b(&state->b);
}

void	pq_del(t_ps_queue *pq)
{
	t_ps_qelem	*tmp;
	t_ps_qelem	*buf;

	tmp = pq->start;
	while (tmp)
	{
		buf = tmp->next;
		free(tmp);
		tmp = buf;
	}
}

void	pq_add(t_ps_queue *pq, t_state state, t_cmds cmd)
{
	int			priority;
	t_ps_qelem	*buf;

//	printf("***************************************************\n");
//	print_stacks(state.a, state.b);
	state.sol.len += (*g_cmds[cmd].func)(&state.a, &state.b);
	treatment(&state);
//	print_stacks(state.a, state.b);
//	printf("***************************************************\n");
	priority = heuristic(state);
//		printf("gg %d vs %d\n", pq->priority, priority);
	if (pq->priority >= priority || pq->start == NULL)
	{
		if (!(buf = malloc(sizeof(t_ps_qelem))))
			ft_exit();
		buf->next = NULL;
		buf->state = state;
		buf->cmd = cmd;
		if (pq->priority > priority || pq->start == NULL)
		{
			pq_del(pq);
			pq->priority = priority;
			pq->start = buf;
			pq->end = buf;
		}
		else
		{
			if (pq->end)
				pq->end->next = buf;
			else
				pq->start = buf;
			pq->end = buf;
		}
	}
}

void	pq_get(t_ps_queue *pq, t_state *state, t_cmds *cmd)
{
	t_ps_qelem	*buf;

	buf = pq->start;
//	printf("before %d\n", tmp->priority);
	pq->start = buf->next;
//	printf("after\n");
	*state = buf->state;
	*cmd = buf->cmd;
	free(buf);
}

t_sol	solve(t_state state)
{
	t_ps_queue	pq;
	t_cmds		i;
	t_cmds		cmd;

	pq = (t_ps_queue){NULL, NULL, heuristic(state)};
	i = 0;
	while (i < LEN)
	{
		if ((*g_cmds[i].check)(&state.a, &state.b))// ubrat '&' !!!
			pq_add(&pq, clone_state(state), i);
		++i;
	}
	while (pq.start)
	{
		pq_get(&pq, &state, &cmd);
		if (state.a.len == 1 && state.b.len == 0)
		{
			print_stacks(state.a, state.b); //
			return (state.sol);
		}
//		print_stacks(state.a, state.b); //
//		printf("|%2d|\n", cmd);
//		printf("\\\\//\n");
		i = 0;
		while (i < LEN)
		{
			if (g_map[cmd][i] && (*g_cmds[i].check)(&state.a, &state.b))// ubrat '&' !!!
			{
//				printf("%d ", i);
				pq_add(&pq, clone_state(state), i);
			}
			++i;
		}
//		printf("\n");
	}
	printf("POLNIY PIZDEC\n");
	return (state.sol);
}

char	is_sorted_a(t_state *state, int len)
{
	int			i;
	t_ps_selem	*tmp;
	t_ps_selem	*next;

	tmp = state->a.top;
	i = 1;
	while (i < len)
	{
		next = tmp->next;
		if (tmp->n > next->n)
			return (0);
		tmp = next;
		++i;
	}
	return (1);
}

char	is_sorted_b(t_state *state, int len)
{
	int			i;
	t_ps_selem	*tmp;
	t_ps_selem	*next;

	tmp = state->b.top;
	i = 1;
	while (i < len)
	{
		next = tmp->next;
		if (tmp->n < next->n)
			return (0);
		tmp = next;
		++i;
	}
	return (1);
}

void	ps_sol_add(t_sol *sol, t_cmds cmd)
{
	t_sol_elem	*tmp;

	if (!(tmp = malloc(sizeof(t_sol_elem))))
		ft_exit();
	tmp->next = sol->top;
	sol->top = tmp;
	tmp->cmd = cmd;
	++sol->len;
}

void	do_cmd(t_state *state, t_cmds cmd)
{
	(*g_cmds[cmd].func)(&state->a, &state->b);
	ps_sol_add(&state->sol, cmd);
//	print_stacks(state->a, state->b);
}

void	sort_b(t_state *state, int sum, int len);
void	sort_a(t_state *state, int sum, int len);

void	sort_a(t_state *state, int sum, int len)
{
	int		avg;
	int		len2;
	int		sum2;
	int		i;

	avg = sum / len;
	if (is_sorted_a(state, len))
		return ;
	len2 = 0;
	sum2 = 0;
	avg = sum / len;
	i = 0;
	while (i < len)
	{
		if (state->a.top->n <= avg)
		{
			sum2 += state->a.top->n;
			++len2;
			do_cmd(state, PB);
		}
		else
			do_cmd(state, RA);
		++i;
	}
	len -= len2;
	sum -= sum2;
	i = 0;
	while (i < len)
	{
		do_cmd(state, RRA);
		++i;
	}
	sort_a(state, sum, len);
	sort_b(state, sum2, len2);
}

void	sort_b(t_state *state, int sum, int len)
{
	int		avg;
	int		len2;
	int		sum2;
	int		i;

	if (is_sorted_b(state, len))
	{
		i = 0;
		while (i < len)
		{
			do_cmd(state, PA);
			++i;
		}
		return ;
	}
	len2 = 0;
	sum2 = 0;
	avg = sum / len;
	i = 0;
	while (i < len)
	{
		if (state->b.top->n > avg)
		{
			sum2 += state->b.top->n;
			++len2;
			do_cmd(state, PA);
		}
		else
			do_cmd(state, RB);
		++i;
	}
	len -= len2;
	sum -= sum2;
	i = 0;
	while (i < len)
	{
		do_cmd(state, RRB);
		++i;
	}
	sort_a(state, sum2, len2);
	sort_b(state, sum, len);
}

#define MIN_NUMBER 2

unsigned int	get_add_number(unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i * i <= len)
		++i;
	--i;
	return (3);
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

typedef struct s_pos	t_pos;

struct					s_pos
{
	unsigned int		ra;
	unsigned int		rra;
	unsigned int		rb;
	unsigned int		rrb;
};

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
//	printf("||| %u + %u = %u |||\n", i->ra, i->rra, state->a.len);
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
//		printf("%u:\tra = %u, rb = %u, rra = %u, rrb = %u\n", tmp->n, i.ra, i.rb, i.rra, i.rrb);
//		printf("min\tra = %u, rb = %u, rra = %u, rrb = %u\n", min_pos.ra, min_pos.rb, min_pos.rra, min_pos.rrb);
		++i.rb;
		--i.rrb;
		tmp = tmp->next;
	}
	shift(state, &min_pos, min);
	do_cmd(state, PA);
/*
	const unsigned int	n = state->b.top->n;
	t_ps_selem			*tmp;
	t_ps_selem			*next;
	++len;
	shift_a(state, i, len - i);
*/
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
//	printf("before: %u, %u\n", len, i);
	len -= i;
	while (--i >= MIN_NUMBER)
		solve_one(state);
//	printf("after:\n");
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
//		printf("before:\n");
			while (buf != tmp)
			{
				next = buf->next;
				free(buf);
				buf = next;
			}
//		printf("after:\n");
			prev->next = tmp;
			start = NULL;
		}
//		printf("gg %p\n", tmp);
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

	void *ptr = malloc(1000);
	sum = 0;
	len = 0;
	state = (t_state){(t_ps_stack){NULL, NULL, 0}, \
			(t_ps_stack){NULL, NULL, 0}, (t_sol){NULL, 0}};
	list = (t_ps_list){NULL, NULL, 0};
	fill_list(&list, ac, av);
	arr = get_arr(list);
	radix_sort(arr, list.len);
//	print_list(list); //
//	printf("\n");
	fill_stack(&state.a, list, &sum, &len);
//	treatment(&state);
//	print_sol(solve(state));
//	print_stacks(state.a, state.b); //
	if (!is_sorted_a(&state, len))
//		sort_a(&state, sum, len);
		sort(&state, len);
//	print_stacks(state.a, state.b); //
//	print_sol(state.sol);
//	printf("|||--- %d ---|||\n", state.sol.len);//
	treatment_sol(&state.sol);
	print_sol(state.sol);
//	printf("|||--- %d ---|||\n", state.sol.len);//
	return (0);
}

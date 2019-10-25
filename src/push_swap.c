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

	return (len <= 1);
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

	return (len <= 1);
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
			(*g_cmds[PB].func)(&state->a, &state->b);
			ps_sol_add(&state->sol, PB);
		}
		else
		{
			(*g_cmds[RA].func)(&state->a, &state->b);
			ps_sol_add(&state->sol, RA);
		}
		++i;
	}
	len -= len2;
	sum -= sum2;
	i = 0;
	while (i < len)
	{
		(*g_cmds[RRA].func)(&state->a, &state->b);
		ps_sol_add(&state->sol, RRA);
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
			(*g_cmds[PA].func)(&state->a, &state->b);
			++state->sol.len;
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
			(*g_cmds[PA].func)(&state->a, &state->b);
			ps_sol_add(&state->sol, PA);
		}
		else
		{
			(*g_cmds[RB].func)(&state->a, &state->b);
			ps_sol_add(&state->sol, RB);
		}
		++i;
	}
	len -= len2;
	sum -= sum2;
	i = 0;
	while (i < len)
	{
		(*g_cmds[RRB].func)(&state->a, &state->b);
		ps_sol_add(&state->sol, RRB);
		++i;
	}
	sort_a(state, sum2, len2);
	sort_b(state, sum, len);
}
/*
#define NUMBER 3

void	init_sort(t_state *state, int len)
{
	const int	step = (len - 1) / (NUMBER - 1);
	

	while (state->a.len >= NUMBER)
	{
		s
	}
}
*/

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
//	print_list(list); //
//	printf("\n");
	fill_stack(&state.a, list, &sum, &len);
//	treatment(&state);
//	print_sol(solve(state));
//	print_stacks(state.a, state.b); //
	sort_a(&state, sum, len);
//	init_sort(&state, len);
//	print_stacks(state.a, state.b); //
	print_sol(state.sol);
//	printf("|||--- %d ---|||\n", state.sol.len);//
	treatment_sol(&state.sol);
//	printf("|||--- %d ---|||\n", state.sol.len);//
	return (0);
}

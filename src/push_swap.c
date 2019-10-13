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
		printf("  --------- || ---------  \n");
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
		printf("|%4d : %-4d             |\n", tmp_a->start + 1, tmp_a->end + 1);
		--len_a;
		tmp_a = tmp_a->next;
	}
	while (len_b > len_a)
	{
		printf("|             %4d : %-4d|\n", tmp_b->start + 1, tmp_b->end + 1);
		--len_b;
		tmp_b = tmp_b->next;
	}
	while (len_b || len_a)
	{
		printf("|%4d : %-4d  %4d : %-4d|\n", tmp_a->start + 1, tmp_a->end + 1, tmp_b->start + 1, tmp_b->end + 1);
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

void	print_sol(t_sol sol)
{
	printf("|||--- %d ---|||\n", sol.len);
	(void)sol;
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

t_node	*pq_add(t_node *pq, t_state state, t_cmds cmd)
{
	int			priority;
	t_node		*tmp;
	t_ps_qelem	*buf;

	(*g_cmds[cmd].func)(&state.a, &state.b);
	++state.sol.len;
//	printf("***************************************************\n");
//	print_stacks(state.a, state.b);
	treatment(&state);
//	print_stacks(state.a, state.b);
//	printf("***************************************************\n");
	priority = state.a.len + state.b.len /*+ state.sol.len*/;
	if (!(buf = malloc(sizeof(t_ps_qelem))))
		ft_exit();
	buf->next = NULL;
	buf->state = state;
	buf->cmd = cmd;
	if ((tmp = avl_find(pq, priority, &ft_cmp)))
	{
		if (tmp->q.end)
			tmp->q.end->next = buf;
		else
			tmp->q.start = buf;
		tmp->q.end = buf;
	}
	else
	{
		tmp = new_node(priority);
		tmp->q.start = buf;
		tmp->q.end = buf;
		pq = avl_insert(pq, tmp, &ft_cmp);
	}
	return (pq);
}

t_node	*pq_get(t_node *pq, t_state *state, t_cmds *cmd)
{
	t_node		*tmp;
	t_ps_qelem	*buf;

	tmp = pq;
	while (tmp->left)
		tmp = tmp->left;
	buf = tmp->q.start;
//	printf("before %d\n", tmp->priority);
	if (buf->next)
		tmp->q.start = buf->next;
	else
		pq = avl_remove(pq, tmp->priority, &ft_cmp);
//	printf("after\n");
	*state = buf->state;
	*cmd = buf->cmd;
	free(buf);
	return (pq);
}

t_sol	solve(t_state state)
{
	t_node	*pq;
	t_cmds	i;
	t_cmds	cmd;

	pq = NULL;
	i = 0;
	while (i < LEN)
	{
		if ((*g_cmds[i].check)(&state.a, &state.b))// ubrat '&' !!!
			pq = pq_add(pq, clone_state(state), i);
		++i;
	}
	while (pq)
	{
		pq = pq_get(pq, &state, &cmd);
		if (state.a.len == 1 && state.b.len == 0)
		{
			printf("gg\n");
			print_stacks(state.a, state.b); //
			avl_infix(pq, &print_node);
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
				pq = pq_add(pq, clone_state(state), i);
			}
			++i;
		}
//		printf("\n");
	}
	printf("POLNIY PIZDEC\n");
	return (state.sol);
}

int		main(int ac, char *av[])
{
	t_ps_stack	a;
	t_ps_stack	b;
	t_state		state;
	t_ps_list	list;
	t_nbr		**arr;

	a = (t_ps_stack){NULL, NULL, 0};
	b = (t_ps_stack){NULL, NULL, 0};
	list = (t_ps_list){NULL, NULL, 0};
	fill_list(&list, ac, av);
	arr = get_arr(list);
	radix_sort(arr, list.len);
	print_list(list); //
	printf("\n");
	fill_stack(&a, list);
	state = (t_state){a, b, (t_sol){NULL, 0}};
	treatment(&state);
	print_stacks(a, b); //
	print_sol(solve(state));
	return (0);
}

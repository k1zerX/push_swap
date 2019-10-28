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
#include "cmds.h"
#include "gvars.h"
#include "radix_sort.h"
#include "sort.h"


#include <stdio.h> //
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
	if (!is_sorted_a(&state))
		sort(&state, len);
	treatment_sol(&state.sol);
	print_sol(state.sol);
	return (0);
}

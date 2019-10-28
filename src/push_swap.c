/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:30:18 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 21:50:29 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "ps_stack.h"
#include "cmds.h"
#include "gvars.h"
#include "radix_sort.h"
#include "sort.h"

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

void	gg(t_state *state)
{
	if (!is_sorted_a(state))
	{
		if (state->a.len == 3)
			sort_three_a(state);
		else
		{
			sort(state);
			treatment_sol(&state->sol);
		}
		print_sol(state->sol);
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
			(t_ps_stack){NULL, NULL, 0}, (t_sol){NULL, NULL, 0}};
	list = (t_ps_list){NULL, NULL, 0};
	fill_list(&list, ac, av);
	if (!list.start)
		return (0);
	arr = get_arr(list);
	radix_sort(arr, list.len);
	fill_stack(&state.a, list, &sum, &len);
	gg(&state);
	ft_del(state, list, arr);
	return (0);
}

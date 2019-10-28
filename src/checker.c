/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:45:06 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 21:07:05 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "gvars.h"
#include "radix_sort.h"
#include "tools.h"
#include "libft.h"

void	read_sol(t_sol *sol)
{
	char	*str;
	t_cmds	cmd;
	int		buf;

	while ((buf = gnl(0, &str)) > 0)
	{
		cmd = 0;
		while (cmd < LEN)
		{
			if (ft_strnequ(str, g_cmds[cmd].name, ft_strlen(str)))
			{
				ps_sol_add(sol, cmd);
				break ;
			}
			++cmd;
		}
		if (cmd == LEN)
			ft_exit();
		free(str);
	}
}

char	do_sol(t_state *state)
{
	t_sol_elem	*tmp;

	tmp = state->sol.top;
	while (tmp)
	{
		if (!(*g_cmds[tmp->cmd].check)(&state->a, &state->b))
			return (0);
		(*g_cmds[tmp->cmd].func)(&state->a, &state->b);
		tmp = tmp->next;
	}
	return (1);
}

int		main(int ac, char *av[])
{
	t_state		state;
	t_ps_list	list;
	t_nbr		**arr;
	int			sum;
	int			len;

	state = (t_state){(t_ps_stack){NULL, NULL, 0}, \
			(t_ps_stack){NULL, NULL, 0}, (t_sol){NULL, NULL, 0}};
	list = (t_ps_list){NULL, NULL, 0};
	fill_list(&list, ac, av);
	if (!list.start)
		return (0);
	arr = get_arr(list);
	radix_sort(arr, list.len);
	fill_stack(&state.a, list, &sum, &len);
	read_sol(&state.sol);
	if (do_sol(&state) && is_sorted_a(&state) && state.b.top == NULL)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	ft_del(state, list, arr);
	return (0);
}

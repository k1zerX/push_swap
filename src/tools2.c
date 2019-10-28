/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 22:01:19 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 22:01:49 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "push_swap.h"

void	ps_sol_add(t_sol *sol, t_cmds cmd)
{
	t_sol_elem	*tmp;

	if (!(tmp = malloc(sizeof(t_sol_elem))))
		ft_exit();
	tmp->cmd = cmd;
	tmp->next = NULL;
	if (sol->bot)
		sol->bot->next = tmp;
	else
		sol->top = tmp;
	sol->bot = tmp;
	++sol->len;
}

void	ft_del_list(t_ps_list list)
{
	t_ps_lelem	*tmp;
	t_ps_lelem	*next;

	tmp = list.start;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->nbr);
		free(tmp);
		tmp = next;
	}
}

void	ft_del_stack(t_ps_stack stack)
{
	t_ps_selem	*tmp;
	t_ps_selem	*next;

	tmp = stack.top;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	ft_del_sol(t_sol sol)
{
	t_sol_elem	*tmp;
	t_sol_elem	*next;

	tmp = sol.top;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	ft_del(t_state state, t_ps_list list, t_nbr **arr)
{
	free(arr);
	ft_del_list(list);
	ft_del_stack(state.a);
	ft_del_stack(state.b);
	ft_del_sol(state.sol);
}

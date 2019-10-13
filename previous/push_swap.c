/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:47:51 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/21 14:04:42 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "ps_stack.h"
#include "cmds.h"
#include "gvars.h"

/**/
#include <stdio.h> // убрать
void	print_stack(t_stack *s)
{
	t_elem		*tmp;

	tmp = s->start;
	while (tmp)
	{
		printf("%d\n", *(int *)tmp->content);
		tmp = tmp->next;
	}
}
/**/
void	ft_print(t_stack *a, t_stack *b)
{
	printf("----------------\n");
	printf("a:\n");
	print_stack(a);
	printf("\n");
	printf("b:\n");
	print_stack(b);
	printf("\n");
	printf("----------------\n");
}
/**/
char	push_swap(t_stack *a, t_stack *b, t_stack *sol, int len)
{
	int		i;

//	ft_print(a, b);
	if (!b->len && is_sorted(a))
		return (1);
	i = -1;
	while (g_cmds[++i].cmd)
	{
//		printf("%s\n", g_cmds[i].cmd);
		if (!g_cmds[i].f(a, b))
			continue ;
		--len;
//		ft_print(a, b);
		ft_stack_push(sol, ft_new_elem(g_cmds[i].cmd, 0, 0));
		if (len)
			return (push_swap(a, b, sol, len));
		g_cmds[i].rf(a, b);
//		ft_print(a, b);
		free(ft_stack_pop(sol));
		++len;
	}
	return (0);
}

void	print_sol(t_stack *sol)
{
	t_elem	*tmp;

	if (!sol->len)
		return ;
	tmp = ft_stack_pop(sol);
	print_sol(sol);
	write(1, tmp->content, ft_strlen(tmp->content));
	write(1, "\n", 1);
	free(tmp);
}

int		main(int ac, char **av)
{
	t_stack		*a;
	t_stack		*b;
	t_stack		*sol;
	int			len;

	if (ac < 2)
		return (0);
	a = ft_stack_new();
	b = ft_stack_new();
	sol = ft_stack_new();
	fill_stack(a, ac, av);
	len = 1;
	while (!push_swap(a, b, sol, len))
		++len;
	print_sol(sol);
	return (0);
}

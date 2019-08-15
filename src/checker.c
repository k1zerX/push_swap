/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 08:33:55 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/21 12:11:03 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_cmd	g_cmds[] =
{
	{"sa", &sa, &sa},
	{"sb", &sb, &sb},
	{"ss", &ss, &ss},
	{"pa", &pa, &pb},
	{"pb", &pb, &pa},
	{"ra", &ra, &rra},
	{"rb", &rb, &rrb},
	{"rr", &rr, &rrr},
	{"rra", &rra, &ra},
	{"rrb", &rrb, &rb},
	{"rrr", &rrr, &rr},
	{NULL, NULL, NULL}
};
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
void	read_sol(t_stack *sol)
{
	char	*tmp;

	if (gnl(0, &tmp, 4) <= 0)
		return ;
	read_sol(sol);
	ft_stack_push(sol, ft_new_elem(tmp, 0, 0));
}

char	check(t_stack *a, t_stack *b, t_stack *sol)
{
	t_elem		*tmp;
	int			i;

	tmp = ft_stack_pop(sol);
	i = 0;
//	printf("check ALERT\n");
	while (g_cmds[i].cmd && !ft_strequ(tmp->content, g_cmds[i].cmd))
	{
//		printf("\"%s\" vs \"%s\"\n", tmp->content, g_cmds[i].cmd);
		i++;
	}
//	printf("\"%s\"\n", g_cmds[i].cmd);
	free(tmp->content);
	free(tmp);
	if (!g_cmds[i].cmd)
		ft_exit(ERROR);
//	printf("before:\n");
//	print_stack(a);
	(*g_cmds[i].f)(a, b);
//	printf("after:\n");
//	print_stack(a);
//	printf("\n");
	if (sol->len > 0)
		return (check(a, b, sol));
	else
		return (is_sorted(a) && !b->len);
}

int		main(int ac, char **av)
{
	t_stack		*a;
	t_stack		*b;
	t_stack		*sol;

	if (ac < 2)
		return (0);
	a = ft_stack_new();
	b = ft_stack_new();
	sol = ft_stack_new();
	fill_stack(a, ac, av);
	read_sol(sol);
	if (check(a, b, sol))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	return (0);
}

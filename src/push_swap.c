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
	char	bln;

	(void)a;
	(void)b;
	(void)sol;

//	ft_print(a, b);
	if (is_sorted(a) && !b->len)
		return (1);
	i = -1;
	while (g_cmds[++i].cmd)
	{
		--len;
//		printf("%s\n", g_cmds[i].cmd);
		bln = g_cmds[i].f(a, b);
//		ft_print(a, b);
		ft_stack_push(sol, ft_new_elem(g_cmds[i].cmd, 0, 0));
		if (len)
			push_swap(a, b, sol, len);
		if (is_sorted(a) && !b->len)
			return (1);
		if (bln)
			g_cmds[i].rf(a, b);
//		ft_print(a, b);
		++len;
		free(ft_stack_pop(sol));
	}
	return (0);
}

void	print_sol(t_stack *sol)
{
	t_elem	*tmp;

	tmp = ft_stack_pop(sol);
	if (sol->len > 0)
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
		len++;
	print_sol(sol);
	return (0);
}

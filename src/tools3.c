/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 22:01:27 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 22:04:11 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "push_swap.h"

t_nbr		**get_arr(t_ps_list list)
{
	t_nbr	**arr;
	int		i;

	if (!(arr = malloc(list.len * sizeof(t_nbr *))))
		ft_exit();
	i = 0;
	while (i < list.len)
	{
		arr[i] = list.start->nbr;
		list.start = list.start->next;
		++i;
	}
	return (arr);
}

t_ps_selem	*get_buf(t_ps_lelem *tmp, t_ps_selem *prev, int *sum, int *len)
{
	t_ps_selem	*buf;

	if (!(buf = malloc(sizeof(t_ps_selem))))
		ft_exit();
	buf->prev = prev;
	buf->n = tmp->nbr->pos;
	*sum += buf->n;
	++*len;
	prev->next = buf;
	return (buf);
}

void		fill_stack(t_ps_stack *stack, t_ps_list list, int *sum, int *len)
{
	t_ps_lelem	*tmp;
	t_ps_selem	*buf;
	t_ps_selem	*prev;

	tmp = list.start;
	if (!(buf = malloc(sizeof(t_ps_selem))))
		ft_exit();
	buf->prev = NULL;
	buf->n = tmp->nbr->pos;
	*sum += buf->n;
	++*len;
	stack->top = buf;
	tmp = tmp->next;
	while (tmp)
	{
		prev = buf;
		buf = get_buf(tmp, prev, sum, len);
		tmp = tmp->next;
	}
	buf->next = NULL;
	stack->bot = buf;
	stack->len = list.len;
}

char		is_sorted_a(t_state *state)
{
	t_ps_selem	*tmp;
	t_ps_selem	*next;

	if ((tmp = state->a.top))
	{
		next = tmp->next;
		while (next)
		{
			if (tmp->n > next->n)
				return (0);
			tmp = next;
			next = tmp->next;
		}
	}
	return (1);
}

char		is_sorted_b(t_state *state)
{
	t_ps_selem	*tmp;
	t_ps_selem	*next;

	if ((tmp = state->b.top))
	{
		next = tmp->next;
		while (next)
		{
			if (tmp->n < next->n)
				return (0);
			tmp = next;
			next = tmp->next;
		}
	}
	return (1);
}

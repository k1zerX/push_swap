/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:45:00 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:45:04 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_list.h"
#include "push_swap.h"

void	list_del(t_ps_list list)
{
	t_ps_lelem	*tmp;
	t_ps_lelem	*buf;

	tmp = list.start;
	while (tmp)
	{
		buf = tmp->next;
		free(tmp);
		tmp = buf;
	}
}

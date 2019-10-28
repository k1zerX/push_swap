/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:41:36 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:41:37 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_LIST_H
# define PS_LIST_H

# include "push_swap.h"
# include <stdlib.h>

typedef struct s_ps_list	t_ps_list;
typedef struct s_ps_lelem	t_ps_lelem;

struct						s_ps_list
{
	t_ps_lelem				*start;
	t_ps_lelem				*end;
	int						len;
};

struct						s_ps_lelem
{
	t_ps_lelem				*next;
	t_nbr					*nbr;
};

void						list_add(t_ps_list *list, t_nbr *nbr);
void						list_del(t_ps_list list);

#endif

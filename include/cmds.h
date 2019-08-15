/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:30:21 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/21 12:58:42 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "push_swap.h"

int		sa(t_stack *a, t_stack *b);
int		sb(t_stack *a, t_stack *b);
int		ss(t_stack *a, t_stack *b);
int		pa(t_stack *a, t_stack *b);
int		pb(t_stack *a, t_stack *b);
int		ra(t_stack *a, t_stack *b);
int		rb(t_stack *a, t_stack *b);
int		rr(t_stack *a, t_stack *b);
int		rra(t_stack *a, t_stack *b);
int		rrb(t_stack *a, t_stack *b);
int		rrr(t_stack *a, t_stack *b);

#endif

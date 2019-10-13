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

#include "ps_stack.h"

typedef struct	s_cmd	t_cmd;
typedef enum	e_cmds	t_cmds;

struct					s_cmd
{
	const char			*name;
	char				(*check)(t_ps_stack *a, t_ps_stack *b);
	void				(*func)(t_ps_stack *a, t_ps_stack *b);
	void				(*cancel)(t_ps_stack *a, t_ps_stack *b);
};

enum					e_cmds
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	LEN
};

extern t_cmd			g_cmds[];
extern char				g_map[LEN][LEN];

char					check_sa(t_ps_stack *a, t_ps_stack *b);
char					check_sb(t_ps_stack *a, t_ps_stack *b);
char					check_ss(t_ps_stack *a, t_ps_stack *b);
char					check_pa(t_ps_stack *a, t_ps_stack *b);
char					check_pb(t_ps_stack *a, t_ps_stack *b);
char					check_ra(t_ps_stack *a, t_ps_stack *b);
char					check_rb(t_ps_stack *a, t_ps_stack *b);
char					check_rr(t_ps_stack *a, t_ps_stack *b);
char					check_rra(t_ps_stack *a, t_ps_stack *b);
char					check_rrb(t_ps_stack *a, t_ps_stack *b);
char					check_rrr(t_ps_stack *a, t_ps_stack *b);
void					sa(t_ps_stack *a, t_ps_stack *b);
void					sb(t_ps_stack *a, t_ps_stack *b);
void					ss(t_ps_stack *a, t_ps_stack *b);
void					pa(t_ps_stack *a, t_ps_stack *b);
void					pb(t_ps_stack *a, t_ps_stack *b);
void					ra(t_ps_stack *a, t_ps_stack *b);
void					rb(t_ps_stack *a, t_ps_stack *b);
void					rr(t_ps_stack *a, t_ps_stack *b);
void					rra(t_ps_stack *a, t_ps_stack *b);
void					rrb(t_ps_stack *a, t_ps_stack *b);
void					rrr(t_ps_stack *a, t_ps_stack *b);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:30:21 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/13 20:30:02 by kbatz            ###   ########.fr       */
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
	char				(*check)(t_ps_stack *a, t_ps_stack *b); // sdelat ne pointer !!!
	int					(*func)(t_ps_stack *a, t_ps_stack *b);
	int					(*cancel)(t_ps_stack *a, t_ps_stack *b);
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
int						sa(t_ps_stack *a, t_ps_stack *b);
int						sb(t_ps_stack *a, t_ps_stack *b);
int						ss(t_ps_stack *a, t_ps_stack *b);
int						pa(t_ps_stack *a, t_ps_stack *b);
int						pb(t_ps_stack *a, t_ps_stack *b);
int						ra(t_ps_stack *a, t_ps_stack *b);
int						rb(t_ps_stack *a, t_ps_stack *b);
int						rr(t_ps_stack *a, t_ps_stack *b);
int						rra(t_ps_stack *a, t_ps_stack *b);
int						rrb(t_ps_stack *a, t_ps_stack *b);
int						rrr(t_ps_stack *a, t_ps_stack *b);

#endif

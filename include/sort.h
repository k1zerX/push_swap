/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:43:03 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 22:00:49 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include "push_swap.h"

void	sort(t_state *state);
void	treatment_sol(t_sol *sol);
void	sort_three_a(t_state *state);
void	sort_three_b(t_state *state);
void	solve_one(t_state *state);
void	to_norm(t_state *state);
void	count_one(t_state *state, t_pos *i, const unsigned int n);
void	do_cmd(t_state *state, t_cmds cmd);
void	shift_a(t_state *state, unsigned int ra, unsigned int rra);

#endif

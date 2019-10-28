/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 09:38:07 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/21 10:43:26 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "ps_stack.h"
# include "ps_list.h"
# include <stdlib.h>
# include <unistd.h>

# define ERROR 0

void	ft_exit(void);
void	fill_list(t_ps_list *list, int ac, char *av[]);
t_nbr	**get_arr(t_ps_list list);
void	fill_stack(t_ps_stack *stack, t_ps_list list, int *sum, int *len);
char	is_sorted_a(t_state *state);
char	is_sorted_b(t_state *state);
void	ps_sol_add(t_sol *sol, t_cmds cmd);
void	ft_del(t_state state, t_ps_list list, t_nbr **arr);

#endif

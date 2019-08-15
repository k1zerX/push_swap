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

# include "push_swap.h"

void	ft_exit(char status);
void	fill_stack(t_stack *a, int ac, char **av);
char	is_sorted(t_stack *a);

#endif

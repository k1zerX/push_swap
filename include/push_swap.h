/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 07:29:36 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/21 13:08:07 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "cmds.h"
# include "tools.h"

# define ERROR 0

typedef struct		s_cmd
{
	char			*cmd;
	int				(*f)(t_stack *a, t_stack *b);
	int				(*rf)(t_stack *a, t_stack *b);
}					t_cmd;

#endif

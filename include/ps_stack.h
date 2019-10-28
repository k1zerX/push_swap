/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:41:49 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:41:50 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_STACK_H
# define PS_STACK_H

# include <stdlib.h>

typedef struct s_ps_stack	t_ps_stack;
typedef struct s_ps_selem	t_ps_selem;

struct						s_ps_stack
{
	t_ps_selem				*top;
	t_ps_selem				*bot;
	unsigned int			len;
};

struct						s_ps_selem
{
	t_ps_selem				*next;
	t_ps_selem				*prev;
	unsigned int			n;
};

#endif

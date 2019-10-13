/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 20:40:40 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/07 00:10:54 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_H
# define AVL_H

# include <stdlib.h>
# include <queue.h>

typedef struct	s_node		t_node;

# define T_AVL_KEY int

# define AVL_KEY priority

# define HEIGHT(x) ((x) ? (x->height) : (0))

struct						s_node
{
	T_AVL_KEY				AVL_KEY;
	t_queue					q;
	t_node					*left;
	t_node					*right;
	unsigned char			height;
};

t_node						*avl_balance(t_node *node);
t_node						*avl_insert(t_node *root, t_node *node, \
									int (*cmp)(T_AVL_KEY a, T_AVL_KEY b));
t_node						*avl_find(t_node *root, T_AVL_KEY key, \
									int (*cmp)(T_AVL_KEY a, T_AVL_KEY b));
void						avl_bfs(t_node *root, void (*f)(t_node *node));
void						avl_infix(t_node *root, void (*f)(t_node *node));
t_node						*avl_remove(t_node *root, T_AVL_KEY key, \
									int (*cmp)(T_AVL_KEY a, T_AVL_KEY b));

#endif

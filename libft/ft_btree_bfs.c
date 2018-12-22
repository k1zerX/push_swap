/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_bfs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:41:56 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/20 13:28:09 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_btree_bfs(t_btree *start, void (*f)(t_btree *))
{
	t_queue		*queue;
	t_btree	*tmp;

	if (!start || !f)
		return ;
	queue = NULL;
	ft_queue_push(&queue, start, sizeof(t_btree));
	while (queue)
	{
		tmp = (t_btree *)ft_queue_pop(&queue)->content;
		(*f)(tmp);
		free(tmp->content);
		free(tmp);
		if (tmp->left)
			ft_queue_push(&queue, tmp->left, sizeof(t_btree));
		if (tmp->right)
			ft_queue_push(&queue, tmp->right, sizeof(t_btree));
	}
}

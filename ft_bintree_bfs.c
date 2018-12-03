/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_bfs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:41:56 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/03 15:44:12 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_bintree_bfs(t_bintree *start, void (*f)(t_bintree *))
{
	t_queue		*queue;
	t_bintree	*tmp;

	if (!start || !f)
		return ;
	queue = NULL;
	ft_queue_push(&queue, start, sizeof(t_bintree));
	while (queue)
	{
		tmp = (t_bintree *)ft_queue_pop(&queue)->content;
		(*f)(tmp);
		free(tmp->content);
		free(tmp);
		if (tmp->left)
			ft_queue_push(&queue, tmp->left, sizeof(t_bintree));
		if (tmp->right)
			ft_queue_push(&queue, tmp->right, sizeof(t_bintree));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:20:02 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/03 12:45:02 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_queue_push(t_queue **queue, void const *content, size_t content_size)
{
	t_queue		*buf;

	if (!queue)
		return ;
	buf = *queue;
	if (buf)
	{
		while (buf->next)
			buf = buf->next;
		buf->next = ft_queue_new(content, content_size);
	}
	else
		*queue = ft_queue_new(content, content_size);
}

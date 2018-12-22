/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:00:24 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/02 05:50:07 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack		*ft_stack_new(void const *content, size_t content_size)
{
	t_stack		*tmp;

	tmp = (t_stack *)malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	if (content)
	{
		tmp->content = malloc(content_size);
		if (!tmp->content)
		{
			free(tmp);
			return (NULL);
		}
		tmp->content_size = content_size;
		ft_memcpy(tmp->content, content, content_size);
	}
	else
	{
		tmp->content = NULL;
		tmp->content_size = 0;
	}
	tmp->next = NULL;
	return (tmp);
}

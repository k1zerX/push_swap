/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:21:26 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/03 12:44:55 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stack_push(t_stack **stack, void const *content, size_t content_size)
{
	t_stack		*tmp;

	if (!stack)
		return ;
	tmp = ft_stack_new(content, content_size);
	tmp->next = *stack;
	*stack = tmp;
}

#include "ps_list.h"
#include "push_swap.h"
#include "tools.h"

void	list_add(t_ps_list *list, t_nbr *nbr)
{
	t_ps_lelem	*tmp;

	if (!(tmp = malloc(sizeof(t_ps_lelem))))
		ft_exit();
	tmp->nbr = nbr;
	tmp->next = NULL;
	if (list->len)
		list->end->next = tmp;
	else
		list->start = tmp;
	list->end = tmp;
	++list->len;
}

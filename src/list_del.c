#include "ps_list.h"
#include "push_swap.h"

void	list_del(t_ps_list list)
{
	t_ps_lelem	*tmp;
	t_ps_lelem	*buf;

	tmp = list.start;
	while (tmp)
	{
		buf = tmp->next;
		free(tmp);
		tmp = buf;
	}
}

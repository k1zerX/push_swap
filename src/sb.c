#include "cmds.h"
#include "ps_stack.h"

char	check_sb(t_ps_stack *a, t_ps_stack *b)
{
	t_ps_selem	*tmp1;
	t_ps_selem	*tmp2;

	(void)a;
	if (!(tmp1 = b->top))
		return (0);
	if (!(tmp2 = tmp1->next) || !(tmp2->next))
		return (0);
	if ((tmp1->end - tmp1->start > 0) || (tmp2->end - tmp2->start > 0))
		return (0);
	return (1);
}

int		sb(t_ps_stack *a, t_ps_stack *b)
{
	t_ps_selem	*tmp1;
	t_ps_selem	*tmp2;
	t_ps_selem	*tmp3;

	(void)a;
	tmp1 = b->top;
	tmp2 = tmp1->next;
	tmp3 = tmp2->next;
	tmp1->prev = tmp2;
	tmp1->next = tmp3;
	tmp2->prev = NULL;
	tmp2->next = tmp1;
	tmp3->prev = tmp1;
	b->top = tmp2;
	return (1);
}

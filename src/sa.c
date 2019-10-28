#include "cmds.h"
#include "ps_stack.h"

char	check_sa(t_ps_stack *a, t_ps_stack *b)
{
	(void)b;
	if (a->top && a->top->next)
		return (1);
	return (0);
}

int		sa(t_ps_stack *a, t_ps_stack *b)
{
	t_ps_selem	*tmp1;
	t_ps_selem	*tmp2;
	t_ps_selem	*tmp3;

	(void)b;
	tmp1 = a->top;
	tmp2 = tmp1->next;
	tmp3 = tmp2->next;
	tmp1->prev = tmp2;
	tmp1->next = tmp3;
	tmp2->prev = NULL;
	tmp2->next = tmp1;
	tmp3->prev = tmp1;
	a->top = tmp2;
	return (1);
}

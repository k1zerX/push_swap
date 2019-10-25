#include "cmds.h"
#include "ps_stack.h"

char	check_pa(t_ps_stack *a, t_ps_stack *b)
{
	(void)a;
	if (!b->top)
		return (0);
	return (1);
}

int		pa(t_ps_stack *a, t_ps_stack *b)
{
	t_ps_selem	*tmp;

	tmp = b->top;
	b->top = tmp->next;
	if (b->top)
		b->top->prev = NULL;
	else
		b->bot = NULL;
	tmp->next = a->top;
	if (a->top)
		a->top->prev = tmp;
	else
		a->bot = tmp;
	a->top = tmp;
	--b->len;
	++a->len;
	return (a->top->end - a->top->start + 1);
}

#include "cmds.h"
#include "ps_stack.h"

char	check_ra(t_ps_stack *a, t_ps_stack *b)
{
	(void)b;
	if (a->top && a->top->next)
		return (1);
	return (0);
}

int		ra(t_ps_stack *a, t_ps_stack *b)
{
	(void)b;
	a->top->prev = a->bot;
	a->bot->next = a->top;
	a->bot = a->top;
	a->top = a->top->next;
	a->top->prev = NULL;
	a->bot->next = NULL;
	return (1);
}

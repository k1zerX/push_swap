#include "cmds.h"
#include "ps_stack.h"

char	check_rra(t_ps_stack *a, t_ps_stack *b)
{
	(void)b;
	if (a->top && a->top->next)
		return (1);
	return (0);
}

int		rra(t_ps_stack *a, t_ps_stack *b)
{
	(void)b;
	a->bot->next = a->top;
	a->top->prev = a->bot;
	a->top = a->bot;
	a->bot = a->bot->prev;
	a->bot->next = NULL;
	a->top->prev = NULL;
	return (a->top->end - a->top->start + 1);
}

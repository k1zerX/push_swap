#include "cmds.h"
#include "ps_stack.h"

char	check_rb(t_ps_stack *a, t_ps_stack *b)
{
	(void)a;
	if (b->top && b->top->next && b->top->next->next)
		return (1);
	return (0);
}

int		rb(t_ps_stack *a, t_ps_stack *b)
{
	(void)a;
	b->top->prev = b->bot;
	b->bot->next = b->top;
	b->bot = b->top;
	b->top = b->top->next;
	b->top->prev = NULL;
	b->bot->next = NULL;
	return (b->bot->end - b->bot->start + 1);
}

#include "cmds.h"
#include "ps_stack.h"

char	check_rrr(t_ps_stack *a, t_ps_stack *b)
{
	return (check_rra(a, b) && check_rrb(a, b) &&
			a->bot->end - a->bot->start == b->bot->end - b->bot->start);
}

int		rrr(t_ps_stack *a, t_ps_stack *b)
{
	rra(a, b);
	rrb(a, b);
	return (a->top->end - a->top->start + b->top->end - b->top->start + 2);
}

#include "cmds.h"
#include "ps_stack.h"

char	check_rr(t_ps_stack *a, t_ps_stack *b)
{
	return (check_ra(a, b) && check_rb(a, b) &&
			a->top->end - a->top->start == b->top->end - b->top->start);
}

int		rr(t_ps_stack *a, t_ps_stack *b)
{
	ra(a, b);
	rb(a, b);
	return (a->bot->end - a->bot->start + b->bot->end - b->bot->start + 2);
}

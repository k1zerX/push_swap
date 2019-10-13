#include "cmds.h"
#include "ps_stack.h"

char	check_rrr(t_ps_stack *a, t_ps_stack *b)
{
	return (check_rra(a, b) && check_rrb(a, b));
}

void	rrr(t_ps_stack *a, t_ps_stack *b)
{
	rra(a, b);
	rrb(a, b);
}

#include "cmds.h"
#include "ps_stack.h"

char	check_rr(t_ps_stack *a, t_ps_stack *b)
{
	return (check_ra(a, b) && check_rb(a, b));
}

void	rr(t_ps_stack *a, t_ps_stack *b)
{
	ra(a, b);
	rb(a, b);
}

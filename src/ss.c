#include "cmds.h"
#include "ps_stack.h"

char	check_ss(t_ps_stack *a, t_ps_stack *b)
{
	return (check_sa(a, b) && check_sb(a, b));
}

int		ss(t_ps_stack *a, t_ps_stack *b)
{
	sa(a, b);
	sb(a, b);
	return (1);
}

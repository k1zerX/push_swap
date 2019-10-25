#include "cmds.h"
#include "gvars.h"
#include "libft.h"
/*
void	read_sol(t_sol *sol)
{
	char	*str;
	int		cmd;

	if (gnl(0, &str, 4) <= 0)
		return ;
	read_sol(sol);
	cmd = 0;
	while (cmd < LEN)
	{
		if (ft_strequ(g_cmds[cmd].name, str))
			ps_sol_add(sol, cmd);
		++cmd;
	}
	ft_stack_push(sol, ft_new_elem(tmp, 0, 0));
	free(str);
}

int		main(int ac, char *av[])
{
	t_state		state;
	t_ps_list	list;
	t_nbr		**arr;

	state = (t_state){(t_ps_stack){NULL, NULL, 0}, \
			(t_ps_stack){NULL, NULL, 0}, (t_sol){NULL, 0}};
	list = (t_ps_list){NULL, NULL, 0};
	fill_list(&list, ac, av);
	arr = get_arr(list);
	radix_sort(arr, list.len);
	fill_stack(&state.a, list, &sum, &len);
	read_sol(state.sol);
	if (check(state))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	return (0);
}*/

int		main(void)
{
	return (0);
}

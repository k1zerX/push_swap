#include "cmds.h"
#include "gvars.h"
#include "radix_sort.h"
#include "tools.h"
#include "libft.h"

void	read_sol(t_sol *sol)
{
	char	*str;
	t_cmds	cmd;

	if (gnl(0, &str) <= 0)
		return ;
	read_sol(sol);
	cmd = 0;
	while (cmd < LEN)
	{
		if (ft_strnequ(str, g_cmds[cmd].name, g_cmds[cmd].len - 1))
			ps_sol_add(sol, cmd);
		++cmd;
	}
	free(str);
}

int		main(int ac, char *av[])
{
	t_state		state;
	t_ps_list	list;
	t_nbr		**arr;
	int			sum;
	int			len;

	state = (t_state){(t_ps_stack){NULL, NULL, 0}, \
			(t_ps_stack){NULL, NULL, 0}, (t_sol){NULL, 0}};
	list = (t_ps_list){NULL, NULL, 0};
	fill_list(&list, ac, av);
	arr = get_arr(list);
	radix_sort(arr, list.len);
	fill_stack(&state.a, list, &sum, &len);
	read_sol(&state.sol);
	if (is_sorted_a(&state) && state.b.top == NULL)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	return (0);
}

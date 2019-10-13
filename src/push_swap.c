#include "tools.h"
#include "ps_stack.h"
#include "cmds.h"
#include "gvars.h"
#include "radix_sort.h"


#include <stdio.h>
void	print_list(t_ps_list list)
{
	t_ps_lelem	*tmp;

	tmp = list.start;
	printf("|-----------------------|\n");
	printf("| len %d \t\t|\n", list.len);
	while (tmp)
	{
		printf("|\t%u\t%d\t|\n", tmp->nbr->pos + 1, tmp->nbr->n);
		tmp = tmp->next;
	}
	printf("|-----------------------|\n");
}

void	print_arr(t_nbr **arr, int len)
{
	int		i;

	i = 0;
	while (i < len - 1)
	{
		printf("%d, ", arr[i]->n);
		++i;
	}
	printf("%d\n", arr[i]->n);
}

int		main(int ac, char *av[])
{
	t_ps_stack	a;
	t_ps_stack	b;
	t_ps_list	list;
	t_nbr		**arr;

	a = (t_ps_stack){NULL, NULL};
	b = (t_ps_stack){NULL, NULL};
	list = (t_ps_list){NULL, NULL, 0};
	fill_list(&list, ac, av);
	arr = get_arr(list);
	radix_sort(arr, list.len);
	print_list(list); //
	fill_stack(&a, list);
	return (0);
}

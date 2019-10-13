#include "ps_list.h"
#include "push_swap.h"

void	lists_zero(t_ps_list lists[10])
{
	lists[0] = (t_ps_list){NULL, NULL, 0};
	lists[1] = (t_ps_list){NULL, NULL, 0};
	lists[2] = (t_ps_list){NULL, NULL, 0};
	lists[3] = (t_ps_list){NULL, NULL, 0};
	lists[4] = (t_ps_list){NULL, NULL, 0};
	lists[5] = (t_ps_list){NULL, NULL, 0};
	lists[6] = (t_ps_list){NULL, NULL, 0};
	lists[7] = (t_ps_list){NULL, NULL, 0};
	lists[8] = (t_ps_list){NULL, NULL, 0};
	lists[9] = (t_ps_list){NULL, NULL, 0};
}

void	lists_del(t_ps_list lists[10])
{
	list_del(lists[0]);
	list_del(lists[1]);
	list_del(lists[2]);
	list_del(lists[3]);
	list_del(lists[4]);
	list_del(lists[5]);
	list_del(lists[6]);
	list_del(lists[7]);
	list_del(lists[8]);
	list_del(lists[9]);
}

char	lists_to_arr(t_ps_list lists[10], t_nbr **arr)
{
	t_ps_lelem	*tmp;
	t_ps_lelem	*buf;
	int			i;
	int			k;
	char		flag;

	flag = 0;
	k = 0;
	i = 0;
	while (i < 10)
	{
		tmp = lists[i].start;
		while (tmp)
		{
			arr[k] = tmp->nbr;
			if (k && arr[k]->n < arr[k - 1]->n)
				flag = 1;
			buf = tmp->next;
			free(tmp);
			tmp = buf;
			++k;
		}
		++i;
	}
	return (flag);
}

char	radix_sort_digit(t_nbr **arr, int len, t_ps_list lists[10], int digit)
{
	int		i;
	char	flag;
	int		buf;

	i = 0;
	flag = 0;
	while (i < len)
	{
		if ((buf = arr[i]->n / digit) != 0)
			flag = 1;
		list_add(lists + buf % 10, arr[i]);
		++i;
	}
	if (flag)
		flag = lists_to_arr(lists, arr);
	else
		lists_del(lists);
	lists_zero(lists);
	return (flag);
}

void	radix_sort(t_nbr **arr, int len)
{
	t_ps_list	lists[10];
	int			digit;
	char		flag;

	lists_zero(lists);
	digit = 1;
	flag = 1;
	while (flag)
	{
		flag = radix_sort_digit(arr, len, lists, digit);
		digit *= 10;
	}
	while (len > 0)
	{
		--len;
		arr[len]->pos = len;
	}
}

#include "tools.h"
#include "push_swap.h"

void	ft_exit(void)
{
	write(2, "error\n", 6);
	exit(1);
}

char	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

char	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

t_nbr	*new_nbr(int n)
{
	t_nbr	*nbr;

	if (!(nbr = malloc(sizeof(t_nbr))))
		ft_exit();
	nbr->n = n;
	return (nbr);
}

void	fill_list_str(t_ps_list *list, char *str)
{
	int		n;

	while (*str)
	{
		if (ft_isdigit(*str))
		{
			n = 0;
			while (ft_isdigit(*str))
			{
				n = n * 10 + (*str - '0');
				++str;
			}
			list_add(list, new_nbr(n));
		}
		else if (ft_isspace(*str))
			++str;
		else if (!*str)
			ft_exit();
	}
}

void	fill_list(t_ps_list *list, int ac, char *av[])
{
	int		i;

	while (ac > 1)
	{
		fill_list_str(list, *++av);
		--ac;
	}
}

t_nbr	**get_arr(t_ps_list list)
{
	t_nbr	**arr;
	int		i;

	if (!(arr = malloc(list.len * sizeof(t_nbr *))))
		ft_exit();
	i = 0;
	while (i < list.len)
	{
		arr[i] = list.start->nbr;
		list.start = list.start->next;
		++i;
	}
	return (arr);
}

void	fill_stack(t_ps_stack *stack, t_ps_list list)
{
	t_ps_lelem	*tmp;
	t_ps_selem	*buf;
	t_ps_selem	*prev;

	tmp = list.start;
	if (!(buf = malloc(sizeof(t_ps_selem))))
		ft_exit();
	buf->prev = NULL;
	buf->start = tmp->nbr->n;
	buf->end = buf->start;
	stack->top = buf;
	tmp = tmp->next;
	while (tmp)
	{
		prev = buf;
		if (!(buf->next = malloc(sizeof(t_ps_selem))))
			ft_exit();
		buf->prev = prev;
		buf->start = tmp->nbr->n;
		buf->end = buf->start;
		prev->next = buf;
		tmp = tmp->next;
	}
	buf->next = NULL;
	stack->bot = buf;
}

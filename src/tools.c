#include "tools.h"
#include "push_swap.h"

void	ft_exit(void)
{
	write(2, "Error\n", 6);
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
	t_nbr			*nbr;

	if (!(nbr = malloc(sizeof(t_nbr))))
		ft_exit();
	nbr->n = (unsigned int)n + ((unsigned int)1 << (sizeof(int) * 8 - 1));
	return (nbr);
}

void	fill_list_str(t_ps_list *list, char *str)
{
	int		n;
	char	sign;

	while (*str)
	{
		if (ft_isdigit(*str) || *str == '-' || *str == '+')
		{
			if (*str == '+')
				++str;
			if (*str == '-')
			{
				sign = -1;
				++str;
			}
			else
				sign = 1;
			n = 0;
			while (ft_isdigit(*str))
			{
				n = n * 10 + (*str - '0') * sign;
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

void	fill_stack(t_ps_stack *stack, t_ps_list list, int *sum, int *len)
{
	t_ps_lelem	*tmp;
	t_ps_selem	*buf;
	t_ps_selem	*prev;

	tmp = list.start;
	if (!(buf = malloc(sizeof(t_ps_selem))))
		ft_exit();
	buf->prev = NULL;
	buf->n = tmp->nbr->pos;
	buf->start = tmp->nbr->pos;
	buf->end = buf->start;
	*sum += buf->n;
	++*len;
	stack->top = buf;
	tmp = tmp->next;
	while (tmp)
	{
		prev = buf;
		if (!(buf = malloc(sizeof(t_ps_selem))))
			ft_exit();
		buf->prev = prev;
		buf->n = tmp->nbr->pos;
		buf->start = tmp->nbr->pos;
		buf->end = buf->start;
		*sum += buf->n;
		++*len;
		prev->next = buf;
		tmp = tmp->next;
	}
	buf->next = NULL;
	stack->bot = buf;
	stack->len = list.len;
}

char	is_sorted_a(t_state *state)
{
	t_ps_selem	*tmp;
	t_ps_selem	*next;

	if ((tmp = state->a.top))
	{
		next = tmp->next;
		while (next)
		{
			next = tmp->next;
			if (tmp->n > next->n)
				return (0);
			tmp = next;
		}
	}
	return (1);
}

char	is_sorted_b(t_state *state)
{
	t_ps_selem	*tmp;
	t_ps_selem	*next;

	if ((tmp = state->b.top))
	{
		next = tmp->next;
		while (next)
		{
			next = tmp->next;
			if (tmp->n < next->n)
				return (0);
			tmp = next;
		}
	}
	return (1);
}

void	ps_sol_add(t_sol *sol, t_cmds cmd)
{
	t_sol_elem	*tmp;

	if (!(tmp = malloc(sizeof(t_sol_elem))))
		ft_exit();
	tmp->next = sol->top;
	sol->top = tmp;
	tmp->cmd = cmd;
	++sol->len;
}

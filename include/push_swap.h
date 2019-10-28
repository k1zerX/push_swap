#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "cmds.h"

# define MIN_NUMBER 2
# define ADD_NUMBER 1

typedef struct s_nbr		t_nbr;
typedef struct s_state		t_state;
typedef struct s_sol		t_sol;
typedef struct s_sol_elem	t_sol_elem;
typedef struct s_pos		t_pos;

struct						s_nbr
{
	unsigned int			n;
	unsigned int			pos;
};

struct						s_sol_elem
{
	t_cmds					cmd;
	t_sol_elem				*next;
};

struct						s_sol
{
	t_sol_elem				*top;
	t_sol_elem				*bot;
	int						len;
};

struct						s_state
{
	t_ps_stack				a;
	t_ps_stack				b;
	t_sol					sol;
};

struct						s_pos
{
	unsigned int			ra;
	unsigned int			rra;
	unsigned int			rb;
	unsigned int			rrb;
};

#endif

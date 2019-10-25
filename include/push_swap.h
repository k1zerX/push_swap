#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "cmds.h"

typedef struct	s_nbr		t_nbr;
typedef struct	s_state		t_state;
typedef struct	s_sol		t_sol;
typedef struct	s_sol_elem	t_sol_elem;

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
	int						len;
};

struct						s_state
{
	t_ps_stack				a;
	t_ps_stack				b;
	t_sol					sol;
};

#endif

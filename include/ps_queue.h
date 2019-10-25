#ifndef PS_QUEUE_H
# define PS_QUEUE_H

# include "cmds.h"
# include "push_swap.h"

typedef struct	s_ps_queue	t_ps_queue;
typedef struct	s_ps_qelem	t_ps_qelem;

struct						s_ps_queue
{
	t_ps_qelem				*start;
	t_ps_qelem				*end;
	int						priority;
};

struct						s_ps_qelem
{
	t_ps_qelem				*next;
	t_state					state;
	t_cmds					cmd;
};

#endif

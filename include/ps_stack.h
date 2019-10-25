#ifndef PS_STACK_H
# define PS_STACK_H

# include <stdlib.h>

typedef struct s_ps_stack	t_ps_stack;
typedef struct s_ps_selem	t_ps_selem;

struct						s_ps_stack
{
	t_ps_selem				*top;
	t_ps_selem				*bot;
	int						len;
};

struct						s_ps_selem
{
	t_ps_selem				*next;
	t_ps_selem				*prev;
	unsigned int			n;
	unsigned int			start;
	unsigned int			end;
};

#endif

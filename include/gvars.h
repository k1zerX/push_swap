#ifndef GVARS_H
# define GVARS_H

#include "cmds.h"

t_cmd	g_cmds[] =
{
	[SA]	= {"sa", &check_sa, &sa, &sa},
	[SB]	= {"sb", &check_sb, &sb, &sb},
	[SS]	= {"ss", &check_ss, &ss, &ss},
	[PA]	= {"pa", &check_pa, &pa, &pb},
	[PB]	= {"pb", &check_pb, &pb, &pa},
	[RA]	= {"ra", &check_ra, &ra, &rra},
	[RB]	= {"rb", &check_rb, &rb, &rrb},
	[RR]	= {"rr", &check_rr, &rr, &rrr},
	[RRA]	= {"rra", &check_rra, &rra, &ra},
	[RRB]	= {"rrb", &check_rrb, &rrb, &rb},
	[RRR]	= {"rrr", &check_rrr, &rrr, &rr},
	[LEN]	= {NULL, NULL, NULL}
};

char	g_map[LEN][LEN] =
{
	[SA] =
	{
		[SA]	= 0,
		[SB]	= 0,
		[SS]	= 0,
		[PA]	= 1,
		[PB]	= 1,
		[RA]	= 1,
		[RB]	= 1,
		[RR]	= 1,
		[RRA]	= 1,
		[RRB]	= 1,
		[RRR]	= 1,
	},
	[SB] =
	{
		[SA]	= 0,
		[SB]	= 0,
		[SS]	= 0,
		[PA]	= 1,
		[PB]	= 1,
		[RA]	= 1,
		[RB]	= 1,
		[RR]	= 1,
		[RRA]	= 1,
		[RRB]	= 1,
		[RRR]	= 1,
	},
	[SS] =
	{
		[SA]	= 0,
		[SB]	= 0,
		[SS]	= 0,
		[PA]	= 1,
		[PB]	= 1,
		[RA]	= 1,
		[RB]	= 1,
		[RR]	= 1,
		[RRA]	= 1,
		[RRB]	= 1,
		[RRR]	= 1,
	},
	[PA] =
	{
		[SA]	= 1,
		[SB]	= 1,
		[SS]	= 1,
		[PA]	= 1,
		[PB]	= 0,
		[RA]	= 1,
		[RB]	= 1,
		[RR]	= 1,
		[RRA]	= 1,
		[RRB]	= 1,
		[RRR]	= 1,
	},
	[PB] =
	{
		[SA]	= 1,
		[SB]	= 1,
		[SS]	= 1,
		[PA]	= 0,
		[PB]	= 1,
		[RA]	= 1,
		[RB]	= 1,
		[RR]	= 1,
		[RRA]	= 1,
		[RRB]	= 1,
		[RRR]	= 1,
	},
	[RA] =
	{
		[SA]	= 1,
		[SB]	= 1,
		[SS]	= 1,
		[PA]	= 1,
		[PB]	= 1,
		[RA]	= 1,
		[RB]	= 0,
		[RR]	= 1,
		[RRA]	= 0,
		[RRB]	= 1,
		[RRR]	= 0,
	},
	[RB] =
	{
		[SA]	= 1,
		[SB]	= 1,
		[SS]	= 1,
		[PA]	= 1,
		[PB]	= 1,
		[RA]	= 0,
		[RB]	= 1,
		[RR]	= 1,
		[RRA]	= 1,
		[RRB]	= 0,
		[RRR]	= 0,
	},
	[RR] =
	{
		[SA]	= 1,
		[SB]	= 1,
		[SS]	= 1,
		[PA]	= 1,
		[PB]	= 1,
		[RA]	= 1,
		[RB]	= 1,
		[RR]	= 1,
		[RRA]	= 0,
		[RRB]	= 0,
		[RRR]	= 0,
	},
	[RRA] =
	{
		[SA]	= 1,
		[SB]	= 1,
		[SS]	= 1,
		[PA]	= 1,
		[PB]	= 1,
		[RA]	= 0,
		[RB]	= 1,
		[RR]	= 0,
		[RRA]	= 1,
		[RRB]	= 0,
		[RRR]	= 1,
	},
	[RRB] =
	{
		[SA]	= 1,
		[SB]	= 1,
		[SS]	= 1,
		[PA]	= 1,
		[PB]	= 1,
		[RA]	= 1,
		[RB]	= 0,
		[RR]	= 0,
		[RRA]	= 0,
		[RRB]	= 1,
		[RRR]	= 1,
	},
	[RRR] =
	{
		[SA]	= 1,
		[SB]	= 1,
		[SS]	= 1,
		[PA]	= 1,
		[PB]	= 1,
		[RA]	= 0,
		[RB]	= 0,
		[RR]	= 0,
		[RRA]	= 1,
		[RRB]	= 1,
		[RRR]	= 1,
	},
};

#endif

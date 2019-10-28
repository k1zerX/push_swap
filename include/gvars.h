/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gvars.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:42:51 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/28 20:43:15 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GVARS_H
# define GVARS_H

# include "cmds.h"

t_cmd	g_cmds[LEN] =
{
	[SA]	= {"sa\n", 3, &check_sa, &sa, &sa},
	[SB]	= {"sb\n", 3, &check_sb, &sb, &sb},
	[SS]	= {"ss\n", 3, &check_ss, &ss, &ss},
	[PA]	= {"pa\n", 3, &check_pa, &pa, &pb},
	[PB]	= {"pb\n", 3, &check_pb, &pb, &pa},
	[RA]	= {"ra\n", 3, &check_ra, &ra, &rra},
	[RB]	= {"rb\n", 3, &check_rb, &rb, &rrb},
	[RR]	= {"rr\n", 3, &check_rr, &rr, &rrr},
	[RRA]	= {"rra\n", 4, &check_rra, &rra, &ra},
	[RRB]	= {"rrb\n", 4, &check_rrb, &rrb, &rb},
	[RRR]	= {"rrr\n", 4, &check_rrr, &rrr, &rr}
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

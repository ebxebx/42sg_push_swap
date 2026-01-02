/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops_apply.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:41:32 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/02 19:02:39 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_ops.h"

void	apply_rot_a(t_ctx *ctx, int cost)
{
	while (cost > 0)
	{
		ra(ctx);
		cost--;
	}
	while (cost < 0)
	{
		rra(ctx);
		cost++;
	}
}

void	apply_rot_b(t_ctx *ctx, int cost)
{
	while (cost > 0)
	{
		rb(ctx);
		cost--;
	}
	while (cost < 0)
	{
		rrb(ctx);
		cost++;
	}
}

void	apply_rr(t_ctx *ctx, int cost)
{
	while (cost > 0)
	{
		rr_any(ctx, 1);
		cost--;
	}
	while (cost < 0)
	{
		rr_any(ctx, -1);
		cost++;
	}
}

/*
	1. Combine rotations (rr / rrr)
	2. Finish A rotations
	3. Finish B rotations
	4. Push A
*/
void	execute_move(t_ctx *ctx, t_move move)
{
	if (move.rr != 0)
		apply_rr(ctx, move.rr);
	if (move.ra != 0)
		apply_rot_a(ctx, move.ra);
	if (move.rb != 0)
		apply_rot_b(ctx, move.rb);
	pa(ctx);
}

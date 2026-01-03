/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_greedy_insertion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:17:57 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 21:42:50 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_debug.h"
#include <limits.h>

static t_list	*find_smallest_larger(t_list *a, int x_rank)
{
	t_list	*cur;
	t_list	*best;
	int		best_rank;
	int		r;

	cur = a;
	best = NULL;
	best_rank = INT_MAX;
	while (cur)
	{
		r = ((t_data *)cur->content)->rank;
		if (r > x_rank && r < best_rank)
		{
			best_rank = r;
			best = cur;
		}
		cur = cur->next;
	}
	if (best)
		debug_printf("find_smallest_larger: best rank: %d\n",
			((t_data *)best->content)->rank);
	return (best);
}

/*
	Calc cost to rot stack_node_b to top
	plus cost to rot stack a target node to top
	If same direction will combine to rr to reduce cost
	All cost to filled to struct move
	move.total is abs(cost_a + cost_b + combined)
*/
t_move	calc_cost_move(t_ctx *ctx, t_list *stack_b_node, int pos_b)
{
	t_move	move;
	t_list	*target_a;
	int		cost_a;
	int		cost_b;
	int		combined;

	target_a = find_smallest_larger(ctx->a,
			((t_data *)stack_b_node->content)->rank);
	if (!target_a)
		target_a = find_min_rank(ctx->a);
	cost_a = calc_rot_cost(calc_index_of_node(ctx->a, target_a), ctx->size_a);
	cost_b = calc_rot_cost(pos_b, ctx->size_b);
	combined = combine_rr(&cost_a, &cost_b);
	move.ra = cost_a;
	move.rb = cost_b;
	move.rr = combined;
	move.total = ft_abs(cost_a) + ft_abs(cost_b) + ft_abs(combined);
	return (move);
}

// calc best cost move to any of b to sorted a
// k = pick from top/bottom k items
t_move	calc_best_cost_move(t_ctx *ctx, int k)
{
	int		pos_b;
	t_move	move;
	t_move	best_move;
	t_list	*node_b;

	pos_b = 0;
	best_move.total = INT_MAX;
	node_b = ctx->b;
	while (pos_b < ctx->size_b)
	{
		if (k <= 0 || pos_b < k || pos_b >= ctx->size_b - k)
		{
			move = calc_cost_move(ctx, node_b, pos_b);
			if (move.total < best_move.total)
				best_move = move;
		}
		node_b = node_b->next;
		pos_b++;
	}
	return (best_move);
}

// Return minimal signed rotation cost to bring position `pos` to top.
// +k means rotate up k times (ra/rb),
// -k means reverse rotate k times (rra/rrb).
int	calc_rot_cost(int pos, int size)
{
	int	up;
	int	down;

	if (size <= 0 || pos < 0 || pos >= size)
		return (0);
	up = pos;
	down = size - pos;
	if (up <= down)
		return (up);
	return (-down);
}

// Combine same-direction rotations into rr/rrr.
// After calling:
// - *cost_a and *cost_b are reduced (leftover individual rotations)
// - return value:
//     > 0 : number of rr to do
//     < 0 : number of rrr to do
//      0  : none to combine
int	combine_rr(int *cost_a, int *cost_b)
{
	int	shared;
	int	abs_a;
	int	abs_b;

	if (!cost_a || !cost_b)
		return (0);
	if (*cost_a > 0 && *cost_b > 0)
	{
		shared = *cost_a;
		if (*cost_b < *cost_a)
			shared = *cost_b;
		return (*cost_a -= shared, *cost_b -= shared, shared);
	}
	if (*cost_a < 0 && *cost_b < 0)
	{
		abs_a = -(*cost_a);
		abs_b = -(*cost_b);
		shared = abs_a;
		if (abs_b < abs_a)
			shared = abs_b;
		return (*cost_a += shared, *cost_b += shared, -shared);
	}
	return (0);
}

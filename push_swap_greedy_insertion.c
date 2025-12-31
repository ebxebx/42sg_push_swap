/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_greedy_insertion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:17:57 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/29 21:05:07 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

int	calc_index_of_node(t_list *stack, t_list *node)
{
	int	ret;

	if (!stack || !node)
		return (-1);
	ret = 0;
	while (stack)
	{
		if (stack == node)
		{
			// printf("calc index of node: %d\n", ret);
			return (ret);
		}
		ret++;
		stack = stack->next;
	}
	return (-1);
}

t_move	calc_cost(t_ctx *ctx, t_list *stack_b_node, int pos_b)
{
	t_move	move;
	t_list	*target_a;
	int		cost_a;
	int		cost_b;
	int		combined;

	// Find target position in A for stack_b_node
	target_a = find_smallest_larger(ctx->a, ((t_data *)stack_b_node->content)->rank);
	if (!target_a)
		target_a = find_min_rank(ctx->a);
	// printf("target_a: rank: %d\n", ((t_data *)target_a->content)->rank);
	// Calculate cost_a
	cost_a = calc_rot_cost(calc_index_of_node(ctx->a, target_a), ctx->size_a);
	// printf("cost_a: %d\n", cost_a);
	// Calculate cost_b
	cost_b = calc_rot_cost(pos_b, ctx->size_b);
	// printf("cost_b: %d\n", cost_b);
	// Combine rr/rrr
	combined = combine_rr(&cost_a, &cost_b);
	// printf("combined: %d\n", combined);
	// Fill move struct
	move.ra = cost_a;
	move.rb = cost_b;
	move.rr = combined;
	move.total = ft_abs(cost_a) + ft_abs(cost_b) + ft_abs(combined);
	// printf("---------->total: %d\n", move.total);
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
		// Find the smallest cost
		if (k <= 0 || pos_b < k || pos_b >= ctx->size_b - k)
		{
			move = calc_cost(ctx, node_b, pos_b);
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

	// printf("pos: %d, size: %d\n", pos, size);
	if (size <= 0 || pos < 0 || pos >= size)
		return (0);
	up = pos;          // ra/rb
	down = size - pos; // rra/rrb
	// printf("up: %d, down: %d\n", up, down);
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
	// Both rotate up => rr
	if (*cost_a > 0 && *cost_b > 0)
	{
		shared = (*cost_a < *cost_b) ? *cost_a : *cost_b;
		*cost_a -= shared;
		*cost_b -= shared;
		return (shared); // rr count
	}
	// Both rotate down => rrr
	if (*cost_a < 0 && *cost_b < 0)
	{
		// shared is the smaller abs
		abs_a = -(*cost_a);
		abs_b = -(*cost_b);
		shared = (abs_a < abs_b) ? abs_a : abs_b;
		*cost_a += shared; // moves toward 0 because negative
		*cost_b += shared;
		return (-shared); // rrr count (negative)
	}
	return (0);
}

t_list	*find_smallest_larger(t_list *a, int x_rank)
{
	t_list	*cur;
	t_list	*best;
	int		best_rank;
	int		r;

	cur = a;
	best = NULL;
	best_rank = INT_MAX;
	// printf("find_smallest_larger: rank: %d\n", x_rank);
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
	{
		// printf("find_smallest_larger: best rank: %d\n", ((t_data *)best->content)->rank);
	}
	return (best);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:17:26 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 21:42:38 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_debug.h"
#include "push_swap_ops.h"
#include <limits.h>

void	lis_push_b(t_ctx *ctx, int *lis_arr, int lis_size)
{
	t_move	best_move;
	t_move	move;
	t_list	*node;

	debug_print_stack(ctx->a, "LIS\n");
	while (ctx->size_a != lis_size)
	{
		best_move.total = INT_MAX;
		node = ctx->a;
		while (node)
		{
			if (!is_in_int_arr(to_data(node->content)->rank, lis_arr, lis_size))
			{
				move.ra = calc_rot_cost(calc_index_of_node(ctx->a, node),
						ctx->size_a);
				move.total = ft_abs(move.ra);
				if (best_move.total > move.total)
					best_move = move;
			}
			node = node->next;
		}
		if (best_move.ra != 0)
			apply_rot_a(ctx, best_move.ra);
		pb(ctx);
	}
}

/*
	May fine tune k value like ....

	if (ctx->size_b >= 125) // need furture test ...
		k = 30;

*/
void	greedy_insertion_push_a(t_ctx *ctx)
{
	t_move	move;
	int		k;

	while (ctx->size_b)
	{
		k = 0;
		if (ctx->size_b >= 200)
			k = 24;
		else if (ctx->size_b >= 150)
			k = 23;
		move = calc_best_cost_move(ctx, k);
		debug_print_stack(ctx->a, "Stack A before exec move!\n");
		execute_move(ctx, move);
		debug_print_stack(ctx->a, "Stack A after exec move!\n");
	}
}

void	sort(t_ctx *ctx)
{
	int	lis_size;
	int	*lis_arr;

	if (check_circular_list(ctx->a, ctx->size_a))
		fix_order_a(ctx);
	if (check_order(ctx->a))
		return ;
	sort_small(ctx);
	lis_size = 0;
	lis_arr = NULL;
	get_longest_increasing_subsequence(ctx->a, ctx->size_a, &lis_size,
		&lis_arr);
	if (lis_size >= (ctx->size_a / 2) + 1)
	{
		lis_push_b(ctx, lis_arr, lis_size);
		free(lis_arr);
	}
	else
		push_b_by_chunk(ctx);
	sort_small(ctx);
	greedy_insertion_push_a(ctx);
	debug_print_stack(ctx->a, "Stack A before fix order!\n");
	if (check_circular_list(ctx->a, ctx->size_a))
		fix_order_a(ctx);
	debug_print_stack(ctx->a, "Stack A Finish!\n");
}

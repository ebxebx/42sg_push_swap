/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_chunking.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:14:26 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 18:02:18 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_debug.h"
#include "push_swap_ops.h"
#include <limits.h>

static int	calc_chunks(t_ctx *ctx)
{
	if (ctx->size_a <= 125)
		return (1);
	else if (ctx->size_a <= 250)
		return (2);
	else if (ctx->size_a <= 375)
		return (3);
	else if (ctx->size_a <= 500)
		return (4);
	else
		return (5);
	return (1);
}

// not helping
void	dynamic_adjust_chunking(int last_ra, int *extra, int *to)
{
	int	threhold;
	int	extra_max;

	threhold = 20;
	extra_max = 30;
	if (last_ra >= threhold)
	{
		debug_printf("last_ra: %d\n", last_ra);
		if (*extra <= extra_max)
		{
			*to -= *extra;
			*extra += 8;
			*to += *extra;
			debug_printf("to updated: %d, extra: %d\n", *to, *extra);
		}
	}
}

// calc which node is best to move, worse than just rotate
void	move_nearest_a_in_range(t_ctx *ctx, int from, int to, int *last_ra)
{
	t_move	best_move;
	t_move	move;
	t_list	*node;
	t_data	*data;

	best_move.total = INT_MAX;
	node = ctx->a;
	while (node)
	{
		data = to_data(node->content);
		if (from <= data->rank && data->rank <= to)
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
	{
		apply_rot_a(ctx, best_move.ra);
		(*last_ra)++;
	}
}

// pb by chunk
void	chunking(t_ctx *ctx)
{
	int		left_in_a;
	int		chunks;
	int		chunk_size;
	int		i;
	int		from;
	int		to;
	t_data	*data;
	int		extra;
	int		last_ra;
	t_list	*node;
	int		j;

	left_in_a = 3;
	debug_print_stack(ctx->a, "Chunking\n");
	chunks = calc_chunks(ctx);
	chunk_size = ctx->size_a / chunks;
	i = 0;
	from = 0;
	while (i < chunks)
	{
		extra = 0;
		last_ra = 0;
		if (i == chunks - 1)
		{
			node = NULL;
			node = find_max_rank(ctx->a);
			// if (node)
			// 	ft_printf("node->rank: %d", ((t_data *)(node->content))->rank);
			to = ((t_data *)(node->content))->rank;
		}
		else
			to = from + chunk_size - 1;
		j = to - from + 1;
		// ft_printf("from: %d, to: %d\n", from, to);
		while (ctx->size_a > left_in_a &&
				((j >= 1) || (extra > 0 && ctx->min_a <= to - extra)
				// try optimize, dynamic expand windows
				))
		{
			debug_printf("i: %d, j: %d, size_a:%d\n", i, j, ctx->size_a);
			debug_print_stack(ctx->a, "CCC\n");
			data = (t_data *)(ctx->a->content);
			if (from <= data->rank && data->rank <= to)
			{
				pb(ctx);
				if (data->rank <= from + ((to - from) / 3)) // /3 or /4 or /5
					rb(ctx);
				j--;
				last_ra = 0;
			}
			else
			{
				ra(ctx);
				last_ra++;
			}
		}
		from = ctx->min_a;
		i++;
		debug_print_stack(ctx->b, "Stack B after chunking:\n");
	}
	debug_print_stack(ctx->a, "Stack A after chunking:\n");

	if (check_circular_list(ctx->a, ctx->size_a))
		fix_order_a(ctx);
	if (check_order(ctx->a))
		return ;
	sort_small(ctx);
}

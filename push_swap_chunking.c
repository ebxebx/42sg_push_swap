/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_chunking.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:14:26 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 15:46:57 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_ops.h"
#include "push_swap_debug.h"
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

// pb by chunk
void	chunking(t_ctx *ctx)
{
	int small_size = 3;
	int	chunks;
	int chunk_size;
	int	i;

	debug_print_stack(ctx->a, "Chunking\n");
	chunks = calc_chunks(ctx);
	chunk_size = ctx->size_a / chunks;
	i = 0;
	int from = 0;
	int to;
	t_data *data;
	while (i < chunks)
	{
		int threhold = 20;
		int extra = 0;
		int extra_max = 30;
		int last_ra = 0;
	
		if (i == chunks - 1){
			t_list *node = NULL;
			node = find_max_rank(ctx->a);
			// if (node)
			// 	ft_printf("node->rank: %d", ((t_data *)(node->content))->rank);
			to = ((t_data *)(node->content))->rank;
			/* if (to - from + 1 > 3)
			 	to -= 3;
			 */// else
			// left one only, because need in sort order
			//	to -= 1;
		}
		else
			to = from + chunk_size - 1;
		int j = to - from + 1;
		// ft_printf("from: %d, to: %d\n", from, to);
		while (ctx->size_a > small_size && (
			(j >= 1)
			|| (
				extra > 0 &&
				ctx->min_a <= to - extra) // try optimize, dynamic expand windows
			)
		)
		{
			// ft_printf("i: %d, j: %d, size_a:%d\n", i, j, ctx->size_a);
			// debug_print_stack(ctx->a, "CCC\n");
			data = (t_data *)(ctx->a->content);
			if (from <= data->rank && data->rank <= to)
			{
				pb(ctx);
				if (ctx->size_a == 0)
				{
					ctx->min_a = -1;
					ctx->max_a = -1;
				}
				else
				{
					ctx->min_a = to_data(find_min_rank(ctx->a)->content)->rank;
					ctx->max_a = to_data(find_max_rank(ctx->a)->content)->rank;
				}
				//ctx->min_b = to_data(find_min_rank(ctx->b)->content)->rank;
				//ctx->max_b = to_data(find_max_rank(ctx->b)->content)->rank;
				// if (data->rank <= ((to - from) / 2)) // wrong
				if (data->rank <= from + ((to - from) / 3)) // /3 or /4 or /5
					rb(ctx);
				j--;
				last_ra = 0;
			}
			else
			{
				int rot = 1;
				if (rot == 1)
				{
					ra(ctx);
					last_ra++;
				}
				else{
				// calc which node is best to move, worse than just rotate
				t_move	best_move;
				t_move	move;
				t_list	*node;
				best_move.total = INT_MAX;
				node = ctx->a;
				while (node)
				{
					data = (t_data *)(node->content);
					if (from <= data->rank && data->rank <= to)
					{
						move.ra = calc_rot_cost(calc_index_of_node(ctx->a, node), ctx->size_a);
						move.total = ft_abs(move.ra);

						if (best_move.total > move.total)
							best_move = move;
					}
					node = node->next;
				}

				// ft_printf("best_move.ra: %d\n", best_move.ra);
				if (best_move.ra != 0)
				{
					apply_rot_a(ctx, best_move.ra);
					last_ra++;
				}
				}

				//debug
				(void) threhold;
				(void) extra_max;
/* 				if (last_ra > 50){
					// ft_printf("a:min/max: %d/%d, extra: %d, from: %d, to: %d\n", ctx->min_a, ctx->max_a, extra, from, to);
					// debug_print_stack(ctx->b, "stack b, error: last_ra > 100\n");
					// debug_print_stack(ctx->a, "stack a, error: last_ra > 100\n");
					exit(1);
				}
				if (last_ra >= threhold)
				{
					// ft_printf("last_ra: %d\n", last_ra);
					// (void)extra_max;
					if (extra <= extra_max)
					{
						extra += 8;
						to = from + chunk_size - 1 + extra;
						// ft_printf("to updated: %d, extra: %d\n", to, extra);
					}
				} */

			}
		}
		// from = to + 1;		
		from = ctx->min_a;		
		i++;
		// debug_print_stack(ctx->b, "Stack B after chunking:\n");
	}
	// debug_print_stack(ctx->a, "Stack A after chunking:\n");
	if (!check_circular_list(ctx->a, ctx->size_a))
	{
		// sort_small(ctx);
		// debug_print_stack(ctx->a, "Stack A after sort small:\n");

		if (ctx->size_a >= 3 && ctx->size_a <= 4)
		{
			while (1)
			{
				sort_small(ctx);
				if (check_circular_list(ctx->a, ctx->size_a))
					break ;
				if (check_order(ctx->a))
					break ;
				if (last_2_reversed(ctx->a))
					rra(ctx);
				else
					ra(ctx);
				// debug_print_stack(ctx->a, "4-5:\n");			
			}
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:44:31 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 15:48:02 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_ops.h"
#include "push_swap_debug.h"

void	sort_small(t_ctx *ctx)
{
	t_data	*data1;
	t_data	*data2;
	t_data	*data3;

	if (ctx->size_a >= 3)
	{
		debug_print_stack(ctx->a, "Sort small start:\n");
		data1 = to_data(ctx->a->content);
		data2 = to_data(ctx->a->next->content);
		data3 = to_data(ctx->a->next->next->content);
		if (data1->rank > data2->rank)
			sa(ctx);
		else if (data2->rank > data3->rank)
		{
			ra(ctx);
			sa(ctx);
		}
	}
}

int	last_2_reversed(t_list *stack)
{
	t_list *prev;

	prev = stack;
	while(stack && stack->next)
	{
		prev = stack;
		stack = stack->next;
	}
	// ft_printf("prev: %p, stack: %p\n", prev, stack);
	return (to_data(prev->content)->rank > to_data(stack->content)->rank);
}

void fix_order_a(t_ctx *ctx)
{
	int	cost_a;
	
	debug_print_stack(ctx->a, "Fix Order: A\n");
	cost_a = calc_rot_cost(
		calc_index_of_node(ctx->a, find_min_rank(ctx->a)), ctx->size_a);
	if (cost_a != 0)
		apply_rot_a(ctx, cost_a);
}

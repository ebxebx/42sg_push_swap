/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_radix_sort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:17:43 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 13:24:19 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_ops.h"
#include "push_swap_debug.h"

static int	bit_count(int max)
{
	int	bits;

	bits = 0;
	while (max > 0)
	{
		bits++;
		max >>= 1;
	}
	return (bits);
}

static int	max_bits(t_list *stack)
{
	t_list	*node;
	int		max;

	node = find_max_rank(stack);
	max = getData(node->content)->rank;
	return (bit_count(max));
}

static void	push_all_to_a(t_ctx *ctx)
{
	while (ctx->size_b)
		pa(ctx);
}

void	radix_sort(t_ctx *ctx)
{
	int	i;
	int	j;
	int	bits;

	i = 0;
	bits = max_bits(ctx->a);
	while (i < bits)
	{
		j = ctx->size_a;
		while (j)
		{
			// ft_printf("size_a: %d, ops: %d\n", ctx->size_a, ctx->ops);
			// print_stack(ctx->a, "Radix Sort: A\n");
			if (getData(ctx->a->content)->rank & (1 << i))
				ra(ctx);
			else
				pb(ctx);
			j--;
		}
		push_all_to_a(ctx);
		i++;
	}
	debug_print_stack(ctx->a, "Radix Sort Final: A\n");
}

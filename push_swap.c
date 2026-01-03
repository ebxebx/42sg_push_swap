/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:33:51 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 15:48:10 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_ops.h"
#include "push_swap_debug.h"
#include <limits.h>

int	main(int ac, char **av)
{
	debug_printf("Hi %s %d", "aa", 1);
	int		result;
	t_ctx	ctx;

	ctx.a = NULL;
	ctx.b = NULL;
	ctx.ops = 0;

	result = read_input(ac, av, &(ctx.a));
	debug_print_stack(ctx.a, "Input:\n");
	if (result != 0)
		return (1);

	calc_rank(ctx.a);
	init_cache_a(&ctx);
	init_cache_b(&ctx);

	if (check_circular_list(ctx.a, ctx.size_a))
		fix_order_a(&ctx);
	if (check_order(ctx.a))
		return (0);
	if (ctx.size_a >= 3 && ctx.size_a <= 4)
	{
		while (1)
		{
			sort_small(&ctx);
			if (check_circular_list(ctx.a, ctx.size_a))
				fix_order_a(&ctx);
			if (check_order(ctx.a))
				return (0);
			if (last_2_reversed(ctx.a))
				rra(&ctx);
			else
				ra(&ctx);
			// debug_print_stack(ctx.a, "4-5:\n");			
		}
		return (0);
	}

	if (ac > 1 && ctx.size_a > 0)
	{
		// Phase 1, Reduce Stage (push to B to reduce A)
		int lis_size = 0;
		int *lis_arr = NULL;
		get_longest_increasing_subsequence(ctx.a, ctx.size_a, &lis_size, &lis_arr);

		// if (lis_size >= ctx.size_a / 3)
		if (lis_size >= (ctx.size_a / 2) + 1)
		{
			debug_print_stack(ctx.a, "LIS\n");
			while (ctx.size_a != lis_size)
			{
				/*int i = 0;
				while (i < lis_size)
				{
					if (((t_data *)ctx.a->content)->rank == lis_arr[i])
					{
						ra(ctx);
						continue;
					}
					i++;
				} */

				// calc which node is best to move
				t_move	best_move;
				t_move	move;
				t_list	*node;
				best_move.total = INT_MAX;
				node = ctx.a;
				while (node)
				{
					if (!is_in_int_arr(to_data(node->content)->rank, lis_arr, lis_size))
					{
						move.ra = calc_rot_cost(calc_index_of_node(ctx.a, node), ctx.size_a);
						move.total = ft_abs(move.ra);

						if (best_move.total > move.total)
							best_move = move;
					}
					node = node->next;
				}

				if (best_move.ra != 0)
					apply_rot_a(&ctx, best_move.ra);

				// ft_printf("LIS Rank: %d\n", lis_arr[i]);
				pb(&ctx);
			}
			debug_print_stack(ctx.a, "Stack A after LIS\n");
			debug_print_stack(ctx.b, "Stack B after LIS\n");
			free(lis_arr);
		}
		else
			chunking(&ctx);

		t_move	move;
		int k;
		while (ctx.size_b)
		{
			// ft_printf("size_b: %d\n", ctx.size_b);
			k = 0;
			if (ctx.size_b >= 200)
			// 23 best
				k = 24; // k = 12 / 8 / 16 for 500 nums
			else if (ctx.size_b >= 150)
			// 23 best
				k = 23; // k = 12 / 8 / 16 for 500 nums
			// if (k > (ctx.size_b / 2))
			/*else if (ctx.size_b >= 125)
				k = 30;*/
			else
				k = 0;
			move = calc_best_cost_move(&ctx, k); 
			debug_print_stack(ctx.a, "Stack A before exec move!\n");
			execute_move(&ctx, move);
			debug_print_stack(ctx.a, "Stack A after exec move!\n");
		}
		debug_print_stack(ctx.a, "Stack A before fix order!\n");
		if (check_circular_list(ctx.a, ctx.size_a))
			fix_order_a(&ctx);
		debug_print_stack(ctx.a, "Stack A Finish!\n");
	}
	else
		ft_putstr_fd("Error\n", 2);

	ft_lstclear(&(ctx.a), free);
	ft_lstclear(&(ctx.b), free);
	return (0);
}

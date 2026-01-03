/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:33:51 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 16:24:16 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_debug.h"
#include "push_swap_ops.h"
#include <limits.h>

int	main(int ac, char **av)
{
	int		result;
	t_ctx	ctx;

	debug_printf("Hi %s %d", "aa", 1);
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
	if (ac > 1 && ctx.size_a > 0)
		sort(&ctx);
	else
		ft_putstr_fd("Error\n", 2);
	ft_lstclear(&(ctx.a), free);
	ft_lstclear(&(ctx.b), free);
	return (0);
}

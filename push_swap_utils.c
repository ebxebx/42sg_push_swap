/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:33:51 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 15:23:54 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

void	init_cache_a(t_ctx *ctx)
{
	t_list	*cur;
	int		r;

	cur = ctx->a;
	ctx->size_a = 0;
	ctx->min_a = INT_MAX;
	ctx->max_a = INT_MIN;
	while (cur)
	{
		r = ((t_data *)cur->content)->rank;
		if (r < ctx->min_a)
			ctx->min_a = r;
		if (r > ctx->max_a)
			ctx->max_a = r;
		ctx->size_a++;
		cur = cur->next;
	}
}

void	init_cache_b(t_ctx *ctx)
{
	t_list	*cur;
	int		r;

	cur = ctx->b;
	ctx->size_b = 0;
	ctx->min_b = INT_MAX;
	ctx->max_b = INT_MIN;
	while (cur)
	{
		r = ((t_data *)cur->content)->rank;
		if (r < ctx->min_b)
			ctx->min_b = r;
		if (r > ctx->max_b)
			ctx->max_b = r;
		ctx->size_b++;
		cur = cur->next;
	}
}

t_data	*to_data(void *ptr)
{
	return ((t_data *)ptr);
}

int	is_in_int_arr(int i, int *arr, int size)
{
	while (size--)
	{
		if (i == arr[0])
			return (1);
		arr++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:33:51 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/02 18:59:28 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

int is_in_int_arr(int i, int *arr, int size)
{
	while (size--)
	{
		if (i == arr[0])
			return (1);
		arr++;
	}
	return (0);
}

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

t_list	*find_min_rank(t_list *a)
{
	t_list *cur;
	t_list *min_node;
	int min_rank;
	int r;

	cur = a;
	min_node = a;
	min_rank = ((t_data *)a->content)->rank;

	while (cur)
	{
		r = ((t_data *)cur->content)->rank;
		if (r < min_rank)
		{
			min_rank = r;
			min_node = cur;
		}
		cur = cur->next;
	}
	return (min_node);
}

t_list	*find_max_rank(t_list *a)
{
	t_list *cur;
	t_list *max_node;
	int max_rank;
	int r;

	cur = a;
	max_node = a;
	max_rank = ((t_data *)a->content)->rank;

	while (cur)
	{
		r = ((t_data *)cur->content)->rank;
		if (r > max_rank)
		{
			max_rank = r;
			max_node = cur;
		}
		cur = cur->next;
	}
	return (max_node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:33:51 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/29 21:01:49 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

// perform ra/rb/rr/rrr first, finaly pa
void	perform_move(t_ctx *ctx, t_move *move)
{
	if (move->rr > 0)
		rotate(&(ctx->a), &(ctx->b), 'c', move->rr);
	else if (move->rr < 0)
		rotate_reverse(&(ctx->a), &(ctx->b), 'c', -move->rr);
	if (move->ra > 0)
		rotate(&(ctx->a), &(ctx->b), 'a', move->ra);
	else if (move->ra < 0)
		rotate_reverse(&(ctx->a), &(ctx->b), 'a', -move->ra);
	if (move->rb > 0)
		rotate(&(ctx->a), &(ctx->b), 'b', move->rb);
	else if (move->rb < 0)
		rotate_reverse(&(ctx->a), &(ctx->b), 'b', -move->rb);
	push(&(ctx->a), &(ctx->b), 'a', 1);
	ctx->size_a++;
	ctx->size_b--;
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

t_data	*create_data(int value, int rank)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->value = value;
	data->rank = rank;
	return (data);
}

int	bit_count(int max)
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

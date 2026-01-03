/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_calc_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:19:28 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 18:05:43 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_debug.h"

int	calc_index_of_node(t_list *stack, t_list *node)
{
	int	ret;

	if (!stack || !node)
		return (-1);
	ret = 0;
	while (stack)
	{
		if (stack == node)
		{
			return (ret);
		}
		ret++;
		stack = stack->next;
	}
	return (-1);
}

void	calc_rank(t_list *stack)
{
	t_list	*current;
	t_list	*next;
	t_data	*data;

	current = stack;
	while (current)
	{
		data = to_data(current->content);
		next = stack;
		while (next)
		{
			if (data->value > to_data(next->content)->value)
				data->rank++;
			next = next->next;
		}
		current = current->next;
	}
}

int	calc_stack_size(t_list *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

void	update_min_max(t_ctx *ctx)
{
	if (ctx->size_a > 0)
	{
		ctx->min_a = to_data(find_min_rank(ctx->a)->content)->rank;
		ctx->max_a = to_data(find_max_rank(ctx->a)->content)->rank;
	}
	else
	{
		ctx->min_a = -1;
		ctx->max_a = -1;
	}
	if (ctx->size_b > 0)
	{
		ctx->min_b = to_data(find_min_rank(ctx->b)->content)->rank;
		ctx->max_b = to_data(find_max_rank(ctx->b)->content)->rank;
	}
	else
	{
		ctx->min_b = -1;
		ctx->max_b = -1;
	}
}

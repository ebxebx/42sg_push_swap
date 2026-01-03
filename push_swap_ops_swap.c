/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops_swap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:36:05 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 15:23:44 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_list **stack)
{
	t_data	*temp;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	temp = to_data((*stack)->content);
	(*stack)->content = to_data((*stack)->next->content);
	(*stack)->next->content = temp;
}

void	sa(t_ctx *ctx)
{
	swap(&(ctx->a));
	ft_printf("sa\n");
	ctx->ops++;
}

void	sb(t_ctx *ctx)
{
	swap(&(ctx->b));
	ft_printf("sb\n");
	ctx->ops++;
}

void	ss(t_ctx *ctx)
{
	swap(&(ctx->a));
	swap(&(ctx->b));
	ft_printf("ss\n");
	ctx->ops++;
}

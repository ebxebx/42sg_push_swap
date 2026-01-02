/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops_swap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:36:05 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/02 18:04:30 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_list **stack)
{
	t_data	*temp;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	temp = getData((*stack)->content);
	(*stack)->content = getData((*stack)->next->content);
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

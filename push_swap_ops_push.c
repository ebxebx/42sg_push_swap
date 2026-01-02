/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops_push.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:31:15 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/02 18:05:41 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_ops.h"

void	pa(t_ctx *ctx)
{
	if (!ctx->b)
		return ;
	ft_lstadd_front(&ctx->a, ft_lstpop(&ctx->b));
	ft_printf("pa\n");
	ctx->ops++;
	ctx->size_b--;
	ctx->size_a++;
}

void	pb(t_ctx *ctx)
{
	if (!ctx->a)
		return ;
	ft_lstadd_front(&ctx->b, ft_lstpop(&ctx->a));
	ft_printf("pb\n");
	ctx->ops++;
	ctx->size_a--;
	ctx->size_b++;
}

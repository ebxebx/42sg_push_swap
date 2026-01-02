/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops_rot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:58:29 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/02 19:03:54 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_ops.h"

void	rot_up(t_list **s);
void	rot_down(t_list **s);

void	ra(t_ctx *ctx)
{
	rot_up(&(ctx->a));
	ft_printf("ra\n");
	ctx->ops++;
}

void	rra(t_ctx *ctx)
{
	rot_up(&(ctx->a));
	ft_printf("rra\n");
	ctx->ops++;
}

void	rb(t_ctx *ctx)
{
	rot_up(&(ctx->b));
	ft_printf("rb\n");
	ctx->ops++;
}

void	rrb(t_ctx *ctx)
{
	rot_up(&(ctx->b));
	ft_printf("rrb\n");
	ctx->ops++;
}

void	rr_any(t_ctx *ctx, int dir)
{
	if (dir > 0)
	{
		rot_up(&(ctx->a));
		rot_up(&(ctx->b));
		ft_printf("rr\n");
		ctx->ops++;
	}
	else if (dir < 0)
	{
		rot_down(&(ctx->a));
		rot_down(&(ctx->b));
		ft_printf("rrr\n");
		ctx->ops++;
	}
}

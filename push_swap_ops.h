/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:41:58 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/02 19:02:20 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_OPS_H
# define PUSH_SWAP_OPS_H

# include "push_swap.h"

void	sa(t_ctx *ctx);
void	sb(t_ctx *ctx);
void	ss(t_ctx *ctx);
void	pa(t_ctx *ctx);
void	pb(t_ctx *ctx);
void	ra(t_ctx *ctx);
void	rb(t_ctx *ctx);
void	rra(t_ctx *ctx);
void	rrb(t_ctx *ctx);
void	rr_any(t_ctx *ctx, int dir);

void	apply_rot_a(t_ctx *ctx, int cost);
void	apply_rot_b(t_ctx *ctx, int cost);
void	apply_rr(t_ctx *ctx, int cost);
void	execute_move(t_ctx *ctx, t_move move);

#endif

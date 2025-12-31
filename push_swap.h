/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:37:32 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/30 19:21:09 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int		value;
	int		rank;
}			t_data;

typedef struct s_move
{
	int		ra;
	int		rb;
	int		rr;
	int		total;
}			t_move;

typedef struct s_ctx
{
	t_list	*a;
	t_list	*b;

	int		size_a;
	int		size_b;

	int		min_a;
	int		max_a;
	int		min_b;
	int		max_b;
}			t_ctx;

void		init_cache_a(t_ctx *ctx);
void		init_cache_b(t_ctx *ctx);

int			compare_rank(t_data *data1, t_data *data2);
void		push(t_list **stack_a, t_list **stack_b, char stack_id, int n);
void		swap(t_list **stack, char stack_id);
void		rotate(t_list **stack_a, t_list **stack_b, char stack_id, int n);
void		rotate_reverse(t_list **stack_a, t_list **stack_b, char stack_id,
				int n);
void		test_move_stack(void);
void		print_stack(t_list *stack);

t_data		*create_data(int value, int rank);
int			bit_count(int max);

int			calc_rot_cost(int pos, int size);
int			combine_rr(int *cost_a, int *cost_b);
void		perform_move(t_ctx *ctx, t_move *move);

t_move		calc_cost(t_ctx *ctx, t_list *stack_b_node, int pos_b);
t_move		calc_best_cost_move(t_ctx *ctx, int k);
int			calc_rot_cost(int pos, int size);
int			calc_index_of_node(t_list *stack, t_list *node);
int			combine_rr(int *cost_a, int *cost_b);
t_list		*find_smallest_larger(t_list *a, int x_rank);
t_list		*find_min_rank(t_list *a);
t_list		*find_max_rank(t_list *a);


int			is_in_int_arr(int i, int *arr, int size);

#endif

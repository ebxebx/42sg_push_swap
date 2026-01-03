/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:37:32 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 18:07:28 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

#ifndef DEBUG
# define DEBUG 0
#endif

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

	int		ops;
}			t_ctx;

// push_swap_read_input.c
int			read_input(int ac, char **av, t_list **stack);

// push_swap_sort.c
void		sort(t_ctx *ctx);

// push_swap_sort_helper.c
void		sort_3_nodes(t_ctx *ctx);
void		sort_small(t_ctx *ctx);
int			last_2_reversed(t_list *stack);
void		fix_order_a(t_ctx *ctx);

// push_swap_chunking.c
void		chunking(t_ctx *ctx);

// push_swap_longest_increasing_subsequence.c
void		get_longest_increasing_subsequence(
				t_list *stack, int stack_size, int *lis_size, int **lis_arr);

// push_swap_utils.c
int			is_in_int_arr(int i, int *arr, int size);
t_data		*to_data(void *ptr);
void		init_cache_a(t_ctx *ctx);
void		init_cache_b(t_ctx *ctx);

void		radix_sort(t_ctx *ctx);

// push_swap_check.c
int			is_sorted_a(t_ctx *ctx);
int			check_circular_list(t_list *stack, int size_a);
int			check_order(t_list *stack);
t_list		*find_min_rank(t_list *a);
t_list		*find_max_rank(t_list *a);

// push_swap_calc_helper.c
int			calc_index_of_node(t_list *stack, t_list *node);
void		calc_rank(t_list *stack);
int			calc_stack_size(t_list *stack);
void		update_min_max(t_ctx *ctx);

t_move		calc_cost_move(t_ctx *ctx, t_list *stack_b_node, int pos_b);
t_move		calc_best_cost_move(t_ctx *ctx, int k);
int			calc_rot_cost(int pos, int size);
int			combine_rr(int *cost_a, int *cost_b);

#endif

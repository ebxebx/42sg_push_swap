/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:37:32 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/02 19:10:31 by zchoo            ###   ########.fr       */
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

void		init_cache_a(t_ctx *ctx);
void		init_cache_b(t_ctx *ctx);

int			compare_rank(t_data *data1, t_data *data2);
void		radix_sort(t_ctx *ctx);

void		print_stack(t_list *stack, char *label);

t_data		*getData(void *ptr);

int			calc_rot_cost(int pos, int size);
int			combine_rr(int *cost_a, int *cost_b);

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

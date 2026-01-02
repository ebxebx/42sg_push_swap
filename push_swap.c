/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:33:51 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/02 20:00:55 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_ops.h"
#include <limits.h>

void	print_stack(t_list *stack, char *label)
{
	t_list *current;
	t_data *data;

	if (!DEBUG)
		return;
	if (label && *label)
		ft_printf("%s", label);

	current = stack;
	while (current)
	{
		data = (t_data *)current->content;
		if (data)
			ft_printf("Value: %d, Rank: %d\n", data->value, data->rank);
		else
			ft_printf("Empty node\n");
		current = current->next;
	}
}

// buggy, something is wrong with the rank checking
int check_rank(t_list *stack)
{
	t_list *current;
	t_data *data;

	current = stack;
	while (current)
	{
		data = (t_data *)current->content;
		// ft_printf("Checking node with Value: %d, Rank: %d\n",data->value, data->rank);
		if (current->next)
		{
			// ft_printf("Next node's Value: %d, Rank: %d\n",
				// ((t_data *)current->next->content)->value,
				// ((t_data *)current->next->content)->rank);
			if (!compare_rank(data, (t_data *)current->next->content))
				return (0);
		}
		else
		{
			// ft_printf("First node's Value: %d, Rank: %d\n",
				// ((t_data *)stack->content)->value,
				// ((t_data *)stack->content)->rank);
			if (!compare_rank(data, (t_data *)stack->content))
				return (0);
		}
        current = current->next;
	}
	return (1);
}

// circular list have max drop_count == 1
int check_circular_list(t_list *stack, int size_a)
{
	t_list *current;
	t_data *data;
	int		drop_count;

	if (size_a == 0)
		return (0);
	drop_count = 0;
	current = stack;
	while (size_a--)
	{
		data = (t_data *)current->content;
		if (current->next && data->value > ((t_data *)current->next->content)->value)
			drop_count++;
		else if (data->value > ((t_data *)stack->content)->value)
			drop_count++;
		if (drop_count > 1)
			return (0);
        current = current->next;
	}
	return (1);
}

int check_order(t_list *stack)
{
	t_list *current;
	t_data *data;

	current = stack;
	while (current)
	{
		data = (t_data *)current->content;
		// ft_printf("Checking node with Value: %d, Rank: %d\n",data->value, data->rank);
		if (current->next)
		{
			// ft_printf("Next node's Value: %d, Rank: %d\n",
				// ((t_data *)current->next->content)->value,
				// ((t_data *)current->next->content)->rank);
			if (data->value > ((t_data *)current->next->content)->value)
				return (0);
		}
        current = current->next;
	}
	return (1);
}

int	compare_rank(t_data *data1, t_data *data2)
{
	if (data2->value > data1->value)
		return (data2->rank > data1->rank);
	if (data2->value < data1->value)
		return (data2->rank < data1->rank);
	return (0);
}

// buggy, due to compare_rank logic
void update_rank(t_list *stack)
{
	t_list	*current;
	t_list	*next;
	t_data	*data;
	int		swapped;
	// int		i = 1;

	swapped = 1;
	current = stack;
	while (!check_rank(stack))
	{
		// ft_printf("%d---->\n", i++);
		swapped = 0;
		data = (t_data *)current->content;
		next = current->next;

		while (next)
		{
			/* // ft_printf("Comparing %d (rank %d) with %d (rank %d)\n",
				((t_data *)next->content)->value, ((t_data *)next->content)->rank,
				data->value, data->rank); */
			if (!compare_rank(data, (t_data *)next->content))
			{
				swapped = data->rank;
				data->rank = ((t_data *)next->content)->rank;
				((t_data *)next->content)->rank = swapped;

				/* // ft_printf("Swapped ranks: %d <-> %d\n", data->rank, ((t_data *)next->content)->rank);
				// ft_printf("After swap: %d (rank %d), %d (rank %d)\n",
					data->value, data->rank,
					((t_data *)next->content)->value, ((t_data *)next->content)->rank); */
			}
			next = next->next;
		}

		/* // ft_printf("=====\n");
		// print_stack(stack); */
		current = current->next;
		if (!current)
			current = stack;
	}
	// ft_printf("+++++\n");
}

void compute_rank(t_list *stack)
{
	t_list	*current;
	t_list	*next;
	t_data	*data;
	// int		i;

	// i = 1;
	current = stack;
	while (current)
	{
		// ft_printf("%d---->\n", i++);
		data = (t_data *)current->content;
		next = stack;

		while (next)
		{
			if (data->value > ((t_data *)next->content)->value)
				data->rank++;
			next = next->next;
		}

		// ft_printf("=====\n");
		// print_stack(stack);
		current = current->next;
	}
	// ft_printf("+++++\n");
}

int duplicate(t_list *stack, int n)
{
	while(stack)
	{
		if (((t_data *)(stack->content))->value == n)
			return (1);

		stack = stack->next;
	}
	return (0);
}

int read_input(int ac, char **av, t_list **stack)
{
	int		rank;
	int		temp;
	int		offset;
	char	**av_backup;
	t_data	*data;

	rank = 0;
	offset = 1;
	av_backup = NULL;
	if (ac == 2)
	{
		av = ft_split(av[1], ' ');
		av_backup = av;
		ac = ft_strarr_len(av) + offset;
		offset = 0;
		// ft_printf("aaa\n");
	}
	while (ac >= 2)
	{
		// ft_printf("bb\n");
		temp = ft_atoi(av[offset]);
		if ((temp == 0 && av[offset][0] != '0')
			|| duplicate(*stack, temp) )
		{
			ft_putstr_fd("Error", 2);
			// ft_putstr_fd(av[offset], 2);
			ft_putstr_fd("\n", 2);

			if (av_backup)
			{
				temp = 0;
				while (av_backup[temp])
				{
					free(av_backup[temp]);
					temp++;
				}
				free(av_backup);
			}

			ft_lstclear(stack, free);

			return (1);
		}
		data = ft_calloc(1, sizeof(t_data));
		data->value = temp;
		data->rank = rank;
		// rank++; // Uncomment this line if you want to increment rank for each element
		// for compute_rank, default rank is 0
		ft_lstadd_back(stack, ft_lstnew(data));
		av++;
		ac--;
		/* ft_putstr_fd("Add: ", 1);
		ft_putnbr_fd(data->value, 1);
		ft_putstr_fd("\n", 1); */
	}
	if (av_backup)
	{
		temp = 0;
		while (av_backup[temp])
		{
			free(av_backup[temp]);
			temp++;
		}
		free(av_backup);
	}

	return (0);
}


int	calc_stack_size(t_list *stack)
{
	int size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}
//ddd
void	get_longest_increasing_subsequence(t_list *stack, int stack_size, int *lis_size, int **lis_arr)
{
	int *arr;
	int *dp;
	int *prev;
	int i, j;

	arr = malloc(sizeof(int) * stack_size);
	dp = malloc(sizeof(int) * stack_size);
	prev = malloc(sizeof(int) * stack_size);

	// dump stack to arr;
	t_list *current = stack;
	i = 0;
	while (current)
	{
		arr[i++] = ((t_data *)current->content)->rank;
		current = current->next;
	}
	// while (i--)
	// {
	// 	// ft_printf("Stack Rank[%d]: %d\n", i, arr[i]);
	// }

	i = 0;
	while (i < stack_size)
	{
		dp[i] = 1;
		prev[i] = -1;
		j = 0;
		while (j < i)
		{
			if (arr[i] > arr[j] 
				&& dp[j] + 1 > dp[i]
			)
			{
				dp[i] = dp[j] + 1;
				prev[i] = j;
			}
			j++;
		}
		i++;
	}
	// while (i--)
	// {
	// 	// ft_printf("DP[%d]: %d, Prev[%d]: %d\n", i, dp[i], i, prev[i]);
	// }

	*lis_size = 0;
	i = 0;
	int last = -1;
	while (i < stack_size)
	{
		if (dp[i] > *lis_size){
			*lis_size = dp[i];
			last = i;
		}
		i++;
	}
	// ft_printf("LIS Size: %d\n", *lis_size);
	// ft_printf("LIS Last: %d\n", last);
	*lis_arr = malloc(sizeof(int) * (*lis_size));
	if (!*lis_arr)
		return ;
	i = *lis_size;
	while (i && (last != -1))
	{
		(*lis_arr)[--i] = arr[last];
		last = prev[last];
	}
	i = 0;
	while (i < *lis_size)
	{
		// ft_printf("LIS Arr[%d]: %d\n", i, (*lis_arr)[i]);
		i++;
	}
	free(arr);
	free(dp);
	free(prev);
}

int	calc_chunks(t_ctx *ctx)
{
	if (ctx->size_a <= 125)
		return (1);
	else if (ctx->size_a <= 250)
		return (2);
	else if (ctx->size_a <= 375)
		return (3);
	else if (ctx->size_a <= 500)
		return (4);
	else
		return (5);
	return (1);
}

t_data	*getData(void *ptr)
{
	return (t_data *)ptr;
}

void sort_small(t_ctx *ctx)
{
	t_data	*data1;
	t_data	*data2;
	t_data	*data3;
	if (ctx->size_a >= 3)
	{
		print_stack(ctx->a, "Sort small start:\n");
		data1 = getData(ctx->a->content);
		data2 = getData(ctx->a->next->content);
		data3 = getData(ctx->a->next->next->content);
		// 2 -> 1 -> 3
		if (data1->rank > data2->rank)
			sa(ctx);
		else if (data2->rank > data3->rank)
		{
			// 1 -> 3 -> 2
			ra(ctx);
			sa(ctx);
		}
	}
}

int	last_2_reversed(t_list *stack)
{
	t_list *prev;

	prev = stack;
	while(stack && stack->next)
	{
		prev = stack;
		stack = stack->next;
	}
	// ft_printf("prev: %p, stack: %p\n", prev, stack);
	return (getData(prev->content)->rank > getData(stack->content)->rank);
}


// pb by chunk
void	chunking(t_ctx *ctx)
{
	// 100 -> 5 chunk
	// 200 -> 7
	// 300 -> 9
	// 400 -> 10
	// 500 -> 11 chunk
	int small_size = 3;
	int	chunks;
	int chunk_size;
	int	i;

	 chunks = calc_chunks(ctx);
	//chunks = 10; // best for 500
	chunk_size = ctx->size_a / chunks;
	i = 0;
	int from = 0;
	int to;
	t_data *data;
	while (i < chunks)
	{
		int threhold = 20;
		int extra = 0;
		int extra_max = 30;
		int last_ra = 0;
	
		if (i == chunks - 1){
			t_list *node = NULL;
			node = find_max_rank(ctx->a);
			// if (node)
			// 	ft_printf("node->rank: %d", ((t_data *)(node->content))->rank);
			to = ((t_data *)(node->content))->rank;
			/* if (to - from + 1 > 3)
			 	to -= 3;
			 */// else
			// left one only, because need in sort order
			//	to -= 1;
		}
		else
			to = from + chunk_size - 1;
		int j = to - from + 1;
		// ft_printf("from: %d, to: %d\n", from, to);
		while (ctx->size_a > small_size && (
			(j >= 1)
			|| (
				extra > 0 &&
				ctx->min_a <= to - extra) // try optimize, dynamic expand windows
			)
		)
		{
			// ft_printf("i: %d, j: %d, size_a:%d\n", i, j, ctx->size_a);
			// print_stack(ctx->a, "CCC\n");
			data = (t_data *)(ctx->a->content);
			if (from <= data->rank && data->rank <= to)
			{
				pb(ctx);
				if (ctx->size_a == 0)
				{
					ctx->min_a = -1;
					ctx->max_a = -1;
				}
				else
				{
					ctx->min_a = getData(find_min_rank(ctx->a)->content)->rank;
					ctx->max_a = getData(find_max_rank(ctx->a)->content)->rank;
				}
				//ctx->min_b = getData(find_min_rank(ctx->b)->content)->rank;
				//ctx->max_b = getData(find_max_rank(ctx->b)->content)->rank;
				// if (data->rank <= ((to - from) / 2)) // wrong
				if (data->rank <= from + ((to - from) / 3)) // /3 or /4 or /5
					rb(ctx);
				j--;
				last_ra = 0;
			}
			else
			{
				int rot = 1;
				if (rot == 1)
				{
					ra(ctx);
					last_ra++;
				}
				else{
				// calc which node is best to move, worse than just rotate
				t_move	best_move;
				t_move	move;
				t_list	*node;
				best_move.total = INT_MAX;
				node = ctx->a;
				while (node)
				{
					data = (t_data *)(node->content);
					if (from <= data->rank && data->rank <= to)
					{
						move.ra = calc_rot_cost(calc_index_of_node(ctx->a, node), ctx->size_a);
						move.total = ft_abs(move.ra);

						if (best_move.total > move.total)
							best_move = move;
					}
					node = node->next;
				}

				// ft_printf("best_move.ra: %d\n", best_move.ra);
				if (best_move.ra != 0)
				{
					apply_rot_a(ctx, best_move.ra);
					last_ra++;
				}
				}

				//debug
				(void) threhold;
				(void) extra_max;
/* 				if (last_ra > 50){
					// ft_printf("a:min/max: %d/%d, extra: %d, from: %d, to: %d\n", ctx->min_a, ctx->max_a, extra, from, to);
					// print_stack(ctx->b, "stack b, error: last_ra > 100\n");
					// print_stack(ctx->a, "stack a, error: last_ra > 100\n");
					exit(1);
				}
				if (last_ra >= threhold)
				{
					// ft_printf("last_ra: %d\n", last_ra);
					// (void)extra_max;
					if (extra <= extra_max)
					{
						extra += 8;
						to = from + chunk_size - 1 + extra;
						// ft_printf("to updated: %d, extra: %d\n", to, extra);
					}
				} */

			}
		}
		// from = to + 1;		
		from = ctx->min_a;		
		i++;
		// print_stack(ctx->b, "Stack B after chunking:\n");
	}
	// print_stack(ctx->a, "Stack A after chunking:\n");
	if (!check_circular_list(ctx->a, ctx->size_a))
	{
		// sort_small(ctx);
		// print_stack(ctx->a, "Stack A after sort small:\n");

		if (ctx->size_a >= 3 && ctx->size_a <= 4)
		{
			while (1)
			{
				sort_small(ctx);
				if (check_circular_list(ctx->a, ctx->size_a))
					break ;
				if (check_order(ctx->a))
					break ;
				if (last_2_reversed(ctx->a))
					rra(ctx);
				else
					ra(ctx);
				// print_stack(ctx->a, "4-5:\n");			
			}
		}
	}
}

void fix_order_a(t_ctx *ctx)
{
	int	cost_a;
	
	cost_a = calc_rot_cost(calc_index_of_node(ctx->a, find_min_rank(ctx->a)), ctx->size_a);
	if (cost_a != 0)
		apply_rot_a(ctx, cost_a);
}

int	main(int ac, char **av)
{
	int		result;
	t_ctx	ctx;

	ctx.a = NULL;
	ctx.b = NULL;
	ctx.ops = 0;

	result = read_input(ac, av, &(ctx.a));
	print_stack(ctx.a, "Input:\n");
	if (result != 0)
		return (1);

	compute_rank(ctx.a);

	init_cache_a(&ctx);
	init_cache_b(&ctx);

	radix_sort(&ctx);
	return (0);

	if (check_circular_list(ctx.a, ctx.size_a))
		fix_order_a(&ctx);
	if (check_order(ctx.a))
		return (0);
	if (ctx.size_a >= 3 && ctx.size_a <= 4)
	{
		while (1)
		{
			sort_small(&ctx);
			if (check_circular_list(ctx.a, ctx.size_a))
				fix_order_a(&ctx);
			if (check_order(ctx.a))
				return (0);
			if (last_2_reversed(ctx.a))
				rra(&ctx);
			else
				ra(&ctx);
			// print_stack(ctx.a, "4-5:\n");			
		}
		return (0);
	}

	if (ac > 1 && ctx.size_a > 0)
	{
		// Phase 1, Reduce Stage (push to B to reduce A)
		int lis_size = 0;
		int *lis_arr = NULL;
		get_longest_increasing_subsequence(ctx.a, calc_stack_size(ctx.a), &lis_size, &lis_arr);

		// if (lis_size >= ctx.size_a / 3)
		if (lis_size >= (ctx.size_a / 2) + 1)
		{
			while (ctx.size_a != lis_size)
			{
				/*int i = 0;
				while (i < lis_size)
				{
					if (((t_data *)ctx.a->content)->rank == lis_arr[i])
					{
						ra(ctx);
						continue;
					}
					i++;
				} */

				// calc which node is best to move
				t_move	best_move;
				t_move	move;
				t_list	*node;
				best_move.total = INT_MAX;
				node = ctx.a;
				while (node)
				{
					if (!is_in_int_arr(getData(node->content)->rank, lis_arr, lis_size))
					{
						move.ra = calc_rot_cost(calc_index_of_node(ctx.a, node), ctx.size_a);
						move.total = ft_abs(move.ra);

						if (best_move.total > move.total)
							best_move = move;
					}
					node = node->next;
				}

				if (best_move.ra != 0)
					apply_rot_a(&ctx, best_move.ra);

				// ft_printf("LIS Rank: %d\n", lis_arr[i]);
				pb(&ctx);
			}
			free(lis_arr);
		}
		else
			chunking(&ctx);

		t_move	move;
		int k;
		while (ctx.size_b)
		{
			// ft_printf("size_b: %d\n", ctx.size_b);
			k = 0;
			if (ctx.size_b >= 200)
			// 23 best
				k = 24; // k = 12 / 8 / 16 for 500 nums
			else if (ctx.size_b >= 150)
			// 23 best
				k = 23; // k = 12 / 8 / 16 for 500 nums
			// if (k > (ctx.size_b / 2))
			/*else if (ctx.size_b >= 125)
				k = 30;*/
			else
				k = 0;
			move = calc_best_cost_move(&ctx, k); 
			execute_move(&ctx, move);
		}
		if (check_circular_list(ctx.a, ctx.size_a))
			fix_order_a(&ctx);
	}
	else
		ft_putstr_fd("Error\n", 2);

	ft_lstclear(&(ctx.a), free);
	ft_lstclear(&(ctx.b), free);
	return (0);
}

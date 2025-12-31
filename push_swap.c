/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:33:51 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/30 19:38:27 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

void print_stack2(t_list *stack, char *label)
{
	if (label && *label)
		printf("%s", label);
	print_stack(stack);
}

void print_stack(t_list *stack)
{
	t_list *current;
	t_data *data;

	current = stack;
	while (current)
	{
		data = (t_data *)current->content;
		if (data)
			printf("Value: %d, Rank: %d\n", data->value, data->rank);
		else
			printf("Empty node\n");
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
		// printf("Checking node with Value: %d, Rank: %d\n",data->value, data->rank);
		if (current->next)
		{
			// printf("Next node's Value: %d, Rank: %d\n",
				// ((t_data *)current->next->content)->value,
				// ((t_data *)current->next->content)->rank);
			if (!compare_rank(data, (t_data *)current->next->content))
				return (0);
		}
		else
		{
			// printf("First node's Value: %d, Rank: %d\n",
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
		// printf("Checking node with Value: %d, Rank: %d\n",data->value, data->rank);
		if (current->next)
		{
			// printf("Next node's Value: %d, Rank: %d\n",
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
		// printf("%d---->\n", i++);
		swapped = 0;
		data = (t_data *)current->content;
		next = current->next;

		while (next)
		{
			/* // printf("Comparing %d (rank %d) with %d (rank %d)\n",
				((t_data *)next->content)->value, ((t_data *)next->content)->rank,
				data->value, data->rank); */
			if (!compare_rank(data, (t_data *)next->content))
			{
				swapped = data->rank;
				data->rank = ((t_data *)next->content)->rank;
				((t_data *)next->content)->rank = swapped;

				/* // printf("Swapped ranks: %d <-> %d\n", data->rank, ((t_data *)next->content)->rank);
				// printf("After swap: %d (rank %d), %d (rank %d)\n",
					data->value, data->rank,
					((t_data *)next->content)->value, ((t_data *)next->content)->rank); */
			}
			next = next->next;
		}

		/* // printf("=====\n");
		// print_stack(stack); */
		current = current->next;
		if (!current)
			current = stack;
	}
	// printf("+++++\n");
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
		// printf("%d---->\n", i++);
		data = (t_data *)current->content;
		next = stack;

		while (next)
		{
			if (data->value > ((t_data *)next->content)->value)
				data->rank++;
			next = next->next;
		}

		// printf("=====\n");
		// print_stack(stack);
		current = current->next;
	}
	// printf("+++++\n");
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
		// printf("aaa\n");
	}
	while (ac >= 2)
	{
		// printf("bb\n");
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

int max_bits(t_list *stack)
{
	int max = 0;
	t_list *current = stack;

	while (current)
	{
		t_data *data = (t_data *)current->content;
		if (data->rank > max)
			max = data->rank;
		current = current->next;
	}
	return (bit_count(max));
}

void radix_sort(t_list **stack_a)
{
	t_list *stack_b;
	int		i;
	int		j;
	int		k;
	int		bits;

	stack_b = NULL;
	i = 0;
	bits = max_bits(*stack_a);
	// printf("Max bits: %d\n", bits);
	while (i < bits)
	{
		j = 0;
		k = ft_lstsize(*stack_a);
		while (j < k)
		{
			// Perform bitwise operations for each bit
			if (((t_data *)(*stack_a)->content)->rank & (1 << i))
				rotate(stack_a, &stack_b, 'a', 1);
			else
				push(stack_a, &stack_b, 'b', 1);
			j++;
		}

		j = 0;
		k = ft_lstsize(stack_b);
		while (j++ < k)
			push(stack_a, &stack_b, 'a', 1);
		i++;
	}
	/* ft_putendl_fd("Stack A after sorting:", 1);
	// print_stack(*stack_a);
	ft_putendl_fd("Stack B after sorting:", 1);
	// print_stack(stack_b); */
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
	// 	// printf("Stack Rank[%d]: %d\n", i, arr[i]);
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
	// 	// printf("DP[%d]: %d, Prev[%d]: %d\n", i, dp[i], i, prev[i]);
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
	// printf("LIS Size: %d\n", *lis_size);
	// printf("LIS Last: %d\n", last);
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
		// printf("LIS Arr[%d]: %d\n", i, (*lis_arr)[i]);
		i++;
	}
	free(arr);
	free(dp);
	free(prev);
}

int	calc_chunks(t_ctx *ctx)
{
	if (ctx->size_a < 100)
	{
		if (80 < ctx->size_a)
			return (4);
		else if (50 < ctx->size_a && ctx->size_a < 80)
			return (3);
		else
			return (2);
	}
	else if (ctx->size_a < 150)
		return (5);
	else if (ctx->size_a < 200)
		return (6);
	else if (ctx->size_a < 250)
		return (7);
	else if (ctx->size_a < 325)
		return (8);
	else if (ctx->size_a < 400)
		return (9);
	else if (ctx->size_a <= 500)
		return (10);
	else
		return (11);
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
		// print_stack2(ctx->a, "Sort small start:\n");
		data1 = getData(ctx->a->content);
		data2 = getData(ctx->a->next->content);
		data3 = getData(ctx->a->next->next->content);
		// 2 -> 1 -> 3
		if (data1->rank > data2->rank)
			swap(&(ctx->a), 'a');
		else if (data2->rank > data3->rank)
		{
			// 1 -> 3 -> 2
			rotate(&(ctx->a), &(ctx->b), 'a', 1);
			swap(&(ctx->a), 'a');
			// rotate_reverse(&(ctx->a), &(ctx->b), 'a', 1);
		}
		// // 3rd > 4th
		// if (ctx->size_a == 5 && 
		// 	data3->rank > getData(ctx->a->next->next->next->content)->rank)
		// {	
		// 	rotate(&(ctx->a), &(ctx->b), 'a', 2);
		// 	swap(&(ctx->a), 'a');
		// }
		// else
		// // 4th
		// if (ctx->size_a == 5 && 
		// 	data3->rank > getData(ctx->a->next->next->next->next->content)->rank)
		// {	
		// 	rotate_reverse(&(ctx->a), &(ctx->b), 'a', 2);
		// 	swap(&(ctx->a), 'a');
		// }
		// print_stack2(ctx->a, "Sort small end:\n");
	}
}

// pb by chunk
void	chunking(t_ctx *ctx)
{
	// 100 -> 5 chunk
	// 200 -> 7
	// 300 -> 9
	// 400 -> 10
	// 500 -> 11 chunk
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
		if (i == chunks - 1){
			t_list *node = NULL;
			node = find_max_rank(ctx->a);
			// if (node)
			// 	printf("node->rank: %d", ((t_data *)(node->content))->rank);
			to = ((t_data *)(node->content))->rank;
			if (to - from + 1 > 3)
			 	to -= 3;
			// else
			// left one only, because need in sort order
			//	to -= 1;
		}
		else
			to = from + chunk_size - 1;
		int j = to - from + 1;
		// printf("from: %d, to: %d\n", from, to);
		while (j >= 1)
		{
			data = (t_data *)(ctx->a->content);
			if (from <= data->rank && data->rank <= to)
			{
				push(&(ctx->a), &(ctx->b), 'b', 1);
				if (data->rank <= (to - from / 2))
					rotate(&(ctx->a), &(ctx->b), 'b', 1);
				ctx->size_a--;
				ctx->size_b++;
				j--;
			}
			else
			{
				// rotate(&(ctx->a), &(ctx->b), 'a', 1);

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

				// printf("best_move.ra: %d\n", best_move.ra);
				if (best_move.ra > 0)
					rotate(&(ctx->a), &(ctx->b), 'a', best_move.ra);
				else if (best_move.ra < 0)
					rotate_reverse(&(ctx->a), &(ctx->b), 'a', -best_move.ra);
			}
		}
		from = to + 1;		
		i++;
		// printf("Stack B after chunking:\n");
		// print_stack(ctx->b);
	}
	// print_stack2(ctx->a, "Stack A after chunking:\n");
	if (!check_circular_list(ctx->a, ctx->size_a))
	{
		sort_small(ctx);
		// print_stack2(ctx->a, "Stack A after sort small:\n");
	}
}

void fix_order_a(t_ctx *ctx)
{
	int	cost_a;
	
	cost_a = calc_rot_cost(calc_index_of_node(ctx->a, find_min_rank(ctx->a)), ctx->size_a);
	if (cost_a > 0)
	{
		rotate(&(ctx->a), &(ctx->b), 'a', cost_a);
	}
	else if (cost_a < 0)
	{
		rotate_reverse(&(ctx->a), &(ctx->b), 'a', -cost_a);
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
	// printf("prev: %p, stack: %p\n", prev, stack);
	return (getData(prev->content)->rank > getData(stack->content)->rank);
}

int	main(int ac, char **av)
{
	// t_list *stack_a;
	// t_list *stack_b;
	int		result;
	t_ctx	ctx;

	// stack_a = NULL;
	// stack_b = NULL;
	ctx.a = NULL;
	ctx.b = NULL;

	result = read_input(ac, av, &(ctx.a));
	if (result != 0)
		return (1);

	compute_rank(ctx.a);
	// test_move_stack();

	init_cache_a(&ctx);
	init_cache_b(&ctx);

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
				rotate_reverse(&(ctx.a), &(ctx.b), 'a', 1);
			else
				rotate(&(ctx.a), &(ctx.b), 'a', 1);
			// print_stack2(ctx.a, "4-5:\n");			
		}
		return (0);
	}

	int sort = 1;
	if (ac > 1 && ctx.size_a > 0)
	{
		if (sort == 0) radix_sort(&(ctx.a));
		else if (sort == 1) {
		// Phase 1, Reduce Stage (push to B to reduce A)
		int lis_size = 0;
		int *lis_arr = NULL;
		get_longest_increasing_subsequence(ctx.a, calc_stack_size(ctx.a), &lis_size, &lis_arr);

		if (lis_size >= ctx.size_a / 2)
		{
			// print_stack2(ctx.a, "LIS:\n");
			while (ctx.size_a != lis_size)
			{
				/*int i = 0;
				while (i < lis_size)
				{
					if (((t_data *)ctx.a->content)->rank == lis_arr[i])
					{
						rotate(&(ctx.a), &(ctx.b), 'a', 1);
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

				if (best_move.ra > 0)
					rotate(&(ctx.a), &(ctx.b), 'a', best_move.ra);
				else if (best_move.ra < 0)
					rotate_reverse(&(ctx.a), &(ctx.b), 'a', -best_move.ra);

				// printf("LIS Rank: %d\n", lis_arr[i]);
				push(&(ctx.a), &(ctx.b), 'b', 1);
				ctx.size_a--;
				ctx.size_b++;
			}




			// printf("Stack A after extracting LIS:\n");
			// print_stack(stack_a);
			// printf("Stack B after extracting LIS:\n");
			// print_stack(stack_b);
			free(lis_arr);
		}
		else
			chunking(&ctx);

		// printf("size_a: %d, size_b: %d\n", ctx.size_a, ctx.size_b);
		// printf("=============================\n");
		// Phase 1, Rebuild Stage (push back to A in order)
		t_move	move;
		// init_cache_a(&ctx);
		// init_cache_b(&ctx);
		while (ctx.size_b)
		{
			// printf("size_b: %d\n", ctx.size_b);
			move = calc_best_cost_move(&ctx);
			perform_move(&ctx, &move);

			// printf("Stack A after perform move:\n");
			// print_stack(ctx.a);
			// printf("Stack B after perform move:\n");
			// print_stack(ctx.b);
		}
		// printf("Stack A after Greedy Insertion:\n");
		// print_stack(ctx.a);
		// printf("Stack B after Greedy Insertion:\n");
		// print_stack(ctx.b);

		int final_rotate = calc_index_of_node(ctx.a, find_min_rank(ctx.a));
		// printf("Final rotate: %d\n", final_rotate);
		rotate(&(ctx.a), &(ctx.b), 'a', final_rotate);
		// printf("Stack A after final rotate:\n");
		// print_stack(ctx.a);

		} // end sort == 1
	}
	else
		ft_putstr_fd("Error\n", 2);

	ft_lstclear(&(ctx.a), free);
	ft_lstclear(&(ctx.b), free);

	// ft_lstclear(&stack_a, free);
	// ft_lstclear(&stack_b, free);
	return (0);
}
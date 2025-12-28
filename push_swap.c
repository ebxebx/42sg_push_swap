/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:33:51 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/28 14:57:49 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		printf("Checking node with Value: %d, Rank: %d\n",data->value, data->rank);
		if (current->next)
		{
			printf("Next node's Value: %d, Rank: %d\n",
				((t_data *)current->next->content)->value,
				((t_data *)current->next->content)->rank);
			if (!compare_rank(data, (t_data *)current->next->content))
				return (0);
		}
		else
		{
			printf("First node's Value: %d, Rank: %d\n",
				((t_data *)stack->content)->value,
				((t_data *)stack->content)->rank);
			if (!compare_rank(data, (t_data *)stack->content))
				return (0);
		}
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
		printf("Checking node with Value: %d, Rank: %d\n",data->value, data->rank);
		if (current->next)
		{
			printf("Next node's Value: %d, Rank: %d\n",
				((t_data *)current->next->content)->value,
				((t_data *)current->next->content)->rank);
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
	int		i = 1;

	swapped = 1;
	current = stack;
	while (!check_rank(stack))
	{
		printf("%d---->\n", i++);
		swapped = 0;
		data = (t_data *)current->content;
		next = current->next;

		while (next)
		{
			/* printf("Comparing %d (rank %d) with %d (rank %d)\n",
				((t_data *)next->content)->value, ((t_data *)next->content)->rank,
				data->value, data->rank); */
			if (!compare_rank(data, (t_data *)next->content))
			{
				swapped = data->rank;
				data->rank = ((t_data *)next->content)->rank;
				((t_data *)next->content)->rank = swapped;

				/* printf("Swapped ranks: %d <-> %d\n", data->rank, ((t_data *)next->content)->rank);
				printf("After swap: %d (rank %d), %d (rank %d)\n",
					data->value, data->rank,
					((t_data *)next->content)->value, ((t_data *)next->content)->rank); */
			}
			next = next->next;
		}

		/* printf("=====\n");
		print_stack(stack); */
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
	int		i;

	i = 1;
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

int read_input(int ac, char **av, t_list **stack)
{
	int		rank;
	int		temp;
	int		offset;
	t_data	*data;

	rank = 0;
	offset = 1;
	if (ac == 2)
	{
		av = ft_split(av[1], ' ');
		ac = ft_strarr_len(av) + offset;
		offset = 0;
	}
	while (ac >= 2)
	{
		temp = ft_atoi(av[offset]);
		if (temp == 0 && av[offset][0] != '0')
		{
			/* ft_putstr_fd("Error, invalid input: ", 2);
			ft_putstr_fd(av[offset], 2);
			ft_putstr_fd("\n", 2); */
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
				rotate(stack_a, &stack_b, 'a');
			else
				push(stack_a, &stack_b, 'b');
			j++;
		}

		j = 0;
		k = ft_lstsize(stack_b);
		while (j++ < k)
			push(stack_a, &stack_b, 'a');
		i++;
	}
	/* ft_putendl_fd("Stack A after sorting:", 1);
	print_stack(*stack_a);
	ft_putendl_fd("Stack B after sorting:", 1);
	print_stack(stack_b); */
}

int	main(int ac, char **av)
{
	t_list *stack_a;
	t_list *stack_b;
	int		result;

	stack_a = NULL;
	stack_b = NULL;

	result = read_input(ac, av, &stack_a);
	if (result != 0)
		return (1);

	compute_rank(stack_a);
	// test_move_stack();

	if (ac > 1)
		radix_sort(&stack_a);

	ft_lstclear(&stack_a, free);
	ft_lstclear(&stack_b, free);	
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:33:51 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/27 22:45:26 by zchoo            ###   ########.fr       */
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
	if (data2->rank < data1->rank && data2->value > data1->value)
		return (0);
	if (data2->rank > data1->rank && data2->value < data1->value)
		return (0);
	return (1);
}

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
			printf("Comparing %d (rank %d) with %d (rank %d)\n",
				((t_data *)next->content)->value, ((t_data *)next->content)->rank,
				data->value, data->rank);
			if (!compare_rank(data, (t_data *)next->content))
			{
				swapped = data->rank;
				data->rank = ((t_data *)next->content)->rank;
				((t_data *)next->content)->rank = swapped;

				printf("Swapped ranks: %d <-> %d\n", data->rank, ((t_data *)next->content)->rank);
				printf("After swap: %d (rank %d), %d (rank %d)\n",
					data->value, data->rank,
					((t_data *)next->content)->value, ((t_data *)next->content)->rank);
			}
			next = next->next;
		}

		printf("=====\n");
		print_stack(stack);
		current = current->next;
		if (!current){
			current = stack;
			swapped = 1;
		}
	}
	printf("+++++\n");
}

int read_input(int ac, char **av, t_list **stack)
{
	int		rank;
	int		temp;
	t_data	*data;

	rank = 1;
	while (ac >= 2)
	{
		temp = ft_atoi(av[1]);
		if (temp == 0 && av[1][0] != '0')
		{
			ft_putstr_fd("Error, invalid input: ", 2);
			ft_putstr_fd(av[1], 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		data = ft_calloc(1, sizeof(t_data));
		data->value = temp;
		data->rank = rank++;
		ft_lstadd_back(stack, ft_lstnew(data));
		av++;
		ac--;
		ft_putstr_fd("Add: ", 1);
		ft_putnbr_fd(data->value, 1);
		ft_putstr_fd("\n", 1);
	}

	return (0);
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

	ft_putstr_fd("Stack A:\n", 1);
	print_stack(stack_a);

	ft_putstr_fd("Sort Stack A's ranks:\n", 1);
	update_rank(stack_a);
	print_stack(stack_a);

/* 
	push(&stack_a, &stack_b, 'b');
	push(&stack_a, &stack_b, 'b');
	push(&stack_a, &stack_b, 'b');
	ft_putstr_fd("Stack A:\n", 1);
	print_stack(stack_a);
	ft_putstr_fd("Stack B:\n", 1);
	print_stack(stack_b);

	push(&stack_a, &stack_b, 'a');
	ft_putstr_fd("Stack A:\n", 1);
	print_stack(stack_a);
	ft_putstr_fd("Stack B:\n", 1);
	print_stack(stack_b);

	// sa
	swap(&stack_a, 'a');
	ft_putstr_fd("Stack A:\n", 1);
	print_stack(stack_a);

	// sb
	swap(&stack_b, 'b');
	ft_putstr_fd("Stack B:\n", 1);
	print_stack(stack_b);

	// ra
	rotate(&stack_a, &stack_b, 'a');
	ft_putstr_fd("Stack A:\n", 1);
	print_stack(stack_a);

	// rb
	rotate(&stack_a, &stack_b, 'b');
	ft_putstr_fd("Stack B:\n", 1);
	print_stack(stack_b);

	// rr
	rotate(&stack_a, &stack_b, 'c');
	ft_putstr_fd("Stack A:\n", 1);
	print_stack(stack_a);
	ft_putstr_fd("Stack B:\n", 1);
	print_stack(stack_b);

	// rra
	rotate_reverse(&stack_a, &stack_b, 'a');
	ft_putstr_fd("Stack A:\n", 1);
	print_stack(stack_a);

	// rra
	rotate_reverse(&stack_a, &stack_b, 'b');
	ft_putstr_fd("Stack B:\n", 1);
	print_stack(stack_b);

	// rrr
	rotate_reverse(&stack_a, &stack_b, 'c');
	ft_putstr_fd("Stack A:\n", 1);
	print_stack(stack_a);
	ft_putstr_fd("Stack B:\n", 1);
	print_stack(stack_b); */

	if (ac > 1)
	{
		int i = 0;
		while (i < bit_count(ac - 1))
		{
			int j = 0;
			int k = ft_lstsize(stack_a);
			while (j < k)
			{
				// Perform bitwise operations for each bit
				if (((t_data *)stack_a->content)->rank & (1 << i))
					rotate(&stack_a, &stack_b, 'a');
				else
					push(&stack_a, &stack_b, 'b');
				j++;
			}

			j = 0;
			k = ft_lstsize(stack_b);
			while (j < k)
			{
				push(&stack_a, &stack_b, 'a');
				j++;
			}
			i++;
		}

		// int j = 0;
		// int k = ft_lstsize(stack_a);
		// while (j < k - 1)
		// {
		// 	rotate(&stack_a, &stack_b, 'a');
		// 	j++;
		// }
		ft_putendl_fd("Stack A after sorting:", 1);
		print_stack(stack_a);
		ft_putendl_fd("Stack B after sorting:", 1);
		print_stack(stack_b);
	}

	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 14:33:49 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/28 15:00:06 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	test_move_stack(void)
{
	t_list *stack_a;
	t_list *stack_b;

	stack_a = NULL;
	stack_b = NULL;

	// Initialize stack_a with some values
	ft_lstadd_back(&stack_a, ft_lstnew(create_data(3, 0)));
	ft_lstadd_back(&stack_a, ft_lstnew(create_data(1, 0)));
	ft_lstadd_back(&stack_a, ft_lstnew(create_data(2, 0)));

	ft_putstr_fd("Initial Stack A:\n", 1);
	print_stack(stack_a);

	// Perform some moves
	push(&stack_a, &stack_b, 'a');
	ft_putstr_fd("After push A:\n", 1);
	print_stack(stack_a);
	print_stack(stack_b);

	swap(&stack_a, 'a');
	ft_putstr_fd("After swap A:\n", 1);
	print_stack(stack_a);

	rotate(&stack_a, &stack_b, 'a');
	ft_putstr_fd("After rotate A:\n", 1);
	print_stack(stack_a);

	rotate_reverse(&stack_a, &stack_b, 'a');
	ft_putstr_fd("After reverse rotate A:\n", 1);
	print_stack(stack_a);

	ft_lstclear(&stack_a, free);
	ft_lstclear(&stack_b, free);
}
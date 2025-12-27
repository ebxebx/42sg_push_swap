/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:36:05 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/27 22:14:42 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_list **stack, char stack_id)
{
	t_data	*data1;
	t_data	*data2;

	if (!stack || !*stack || !(*stack)->next)
		return ;

	data1 = (t_data *)(*stack)->content;
	data2 = (t_data *)(*stack)->next->content;

	(*stack)->content = data2;
	(*stack)->next->content = data1;

	if (stack_id == 'a')
		ft_putstr_fd("sa\n", 1);
	else if (stack_id == 'b')
		ft_putstr_fd("sb\n", 1);
}

void	push(t_list **stack_a, t_list **stack_b, char stack_id)
{
	if (stack_id != 'a' && stack_id != 'b')
	{
		ft_putstr_fd("Error: Invalid stack identifier. Use 'a' or 'b'.\n", 2);
		return ;
	}
	if (stack_id == 'a' && (!stack_b || !*stack_b))
	{
		ft_putstr_fd("Error: Stack B is empty\n", 2);
		return ;
	}
	if (stack_id == 'b' && (!stack_a || !*stack_a))
	{
		ft_putstr_fd("Error: Stack A is empty\n", 2);
		return ;
	}
	if (stack_id == 'a' && stack_b && *stack_b)
	{
		ft_lstadd_front(stack_a, ft_lstpop(stack_b));
		ft_putstr_fd("pa\n", 1);
	}
	else if (stack_id == 'b' && stack_a && *stack_a)
	{
		ft_lstadd_front(stack_b, ft_lstpop(stack_a));
		ft_putstr_fd("pb\n", 1);
	}
}

void	rotate(t_list **stack_a, t_list **stack_b, char stack_id)
{
	if (stack_id == 'a' || stack_id == 'c')
	{
		if (!stack_a || !*stack_a || !(*stack_a)->next)
			return ;

		ft_lstadd_back(stack_a, ft_lstpop(stack_a));
	}
	if (stack_id == 'b' || stack_id == 'c')
	{
		if (!stack_b || !*stack_b || !(*stack_b)->next)
			return ;
		ft_lstadd_back(stack_b, ft_lstpop(stack_b));
	}
	if (stack_id == 'c')
		ft_putstr_fd("rr\n", 1);
	else if (stack_id == 'a')
		ft_putstr_fd("ra\n", 1);
	else if (stack_id == 'b')
		ft_putstr_fd("rb\n", 1);
}

void	rotate_reverse(t_list **stack_a, t_list **stack_b, char stack_id)
{
	t_list	*last;

	if (stack_id == 'a' || stack_id == 'c')
	{
		if (!stack_a || !*stack_a || !(*stack_a)->next)
			return ;
		last = ft_lstpop_back(stack_a);
		ft_lstadd_front(stack_a, last);
	}
	if (stack_id == 'b' || stack_id == 'c')
	{
		if (!stack_b || !*stack_b || !(*stack_b)->next)
			return ;
		last = ft_lstpop_back(stack_b);
		ft_lstadd_front(stack_b, last);
	}
	if (stack_id == 'c')
		ft_putstr_fd("rrr\n", 1);
	else if (stack_id == 'a')
		ft_putstr_fd("rra\n", 1);
	else if (stack_id == 'b')
		ft_putstr_fd("rrb\n", 1);
}
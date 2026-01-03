/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:03:47 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 17:53:20 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_debug.h"

int	is_sorted_a(t_ctx *ctx)
{
	if (check_circular_list(ctx->a, ctx->size_a))
		fix_order_a(ctx);
	return (check_order(ctx->a));
}

// circular list have max drop_count == 1
int	check_circular_list(t_list *stack, int size_a)
{
	t_list	*current;
	t_data	*data;
	int		drop_count;

	debug_print_stack(stack, "Check Circular List\n");
	if (size_a == 0)
		return (0);
	drop_count = 0;
	current = stack;
	while (size_a--)
	{
		data = to_data(current->content);
		if (current->next)
		{
			if (data->rank > to_data(current->next->content)->rank)
				drop_count++;
		}
		else if (data->rank > ((t_data *)stack->content)->rank)
			drop_count++;
		if (drop_count > 1)
			return (0);
		current = current->next;
	}
	return (1);
}

// check is sorted from small to lagest without wrap around
int	check_order(t_list *stack)
{
	t_list	*current;
	t_data	*data;

	debug_print_stack(stack, "Check Order\n");
	current = stack;
	while (current)
	{
		data = to_data(current->content);
		if (current->next)
		{
			if (data->rank > to_data(current->next->content)->rank)
				return (0);
		}
		current = current->next;
	}
	return (1);
}

t_list	*find_min_rank(t_list *a)
{
	t_list	*cur;
	t_list	*min_node;
	int		min_rank;
	int		r;

	cur = a;
	min_node = a;
	min_rank = ((t_data *)a->content)->rank;
	while (cur)
	{
		r = ((t_data *)cur->content)->rank;
		if (r < min_rank)
		{
			min_rank = r;
			min_node = cur;
		}
		cur = cur->next;
	}
	return (min_node);
}

t_list	*find_max_rank(t_list *a)
{
	t_list	*cur;
	t_list	*max_node;
	int		max_rank;
	int		r;

	cur = a;
	max_node = a;
	max_rank = ((t_data *)a->content)->rank;
	while (cur)
	{
		r = ((t_data *)cur->content)->rank;
		if (r > max_rank)
		{
			max_rank = r;
			max_node = cur;
		}
		cur = cur->next;
	}
	return (max_node);
}

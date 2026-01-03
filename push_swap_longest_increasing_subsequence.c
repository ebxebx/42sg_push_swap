/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_longest_increasing_subsequence.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:32:48 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 21:37:18 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_debug.h"

static int	*dump_to_arr(t_list *stack, int stack_size)
{
	t_list	*current;
	int		*arr;
	int		i;

	arr = malloc(sizeof(int) * stack_size);
	if (!arr)
		return (NULL);
	current = stack;
	i = 0;
	while (current)
	{
		arr[i++] = to_data(current->content)->rank;
		current = current->next;
	}
	return (arr);
}

static int	init_helper_arr(int **dp, int **prev, int stack_size)
{
	*dp = malloc(sizeof(int) * stack_size);
	if (!(*dp))
		return (0);
	*prev = malloc(sizeof(int) * stack_size);
	if (!(*prev))
		return (free(*dp), 0);
	while (stack_size--)
	{
		(*dp)[stack_size] = 1;
		(*prev)[stack_size] = -1;
	}
	return (1);
}

/*
	update last = index of last number of the lis list in arr
	return lis size
*/
static int	calc_lis(int *arr, int **dp, int **prev, int *last)
{
	int	i;
	int	j;
	int	lis_size;

	lis_size = 0;
	i = -1;
	while (++i < (int)(sizeof(*arr) / sizeof(int)))
	{
		j = -1;
		while (++j < i)
		{
			if (arr[i] > arr[j] && (*dp)[j] + 1 > (*dp)[i])
			{
				(*dp)[i] = (*dp)[j] + 1;
				(*prev)[i] = j;
			}
		}
		if ((*dp)[i] > lis_size)
		{
			lis_size = (*dp)[i];
			*last = i;
		}
	}
	return (lis_size);
}

static int	*dump_to_lis_arr(int *arr, int *prev, int lis_size, int last)
{
	int	*lis_arr;

	lis_arr = malloc(sizeof(int) * (lis_size));
	if (!lis_arr)
		return (NULL);
	while (lis_size && (last != -1))
	{
		lis_arr[--lis_size] = arr[last];
		last = prev[last];
	}
	return (lis_arr);
}

void	get_longest_increasing_subsequence(t_list *stack, int stack_size,
		int *lis_size, int **lis_arr)
{
	int	*arr;
	int	*dp;
	int	*prev;
	int	i;
	int	last;

	arr = dump_to_arr(stack, stack_size);
	if (!init_helper_arr(&dp, &prev, stack_size))
		return ;
	*lis_size = 0;
	i = 0;
	last = -1;
	*lis_size = calc_lis(arr, &dp, &prev, &last);
	debug_printf("LIS Size: %d\n", *lis_size);
	debug_printf("LIS Last: %d\n", last);
	*lis_arr = dump_to_lis_arr(arr, prev, *lis_size, last);
	i = 0;
	while (i < *lis_size)
	{
		debug_printf("LIS Arr[%d]: %d\n", i, (*lis_arr)[i]);
		i++;
	}
	free(arr);
	free(dp);
	free(prev);
}

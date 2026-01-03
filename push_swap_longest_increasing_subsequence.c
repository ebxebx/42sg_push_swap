/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_longest_increasing_subsequence.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:32:48 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 15:33:38 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
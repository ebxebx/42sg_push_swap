/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:37:32 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/28 14:55:54 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct data
{
	int	value;
	int	rank;
}		t_data;

int		compare_rank(t_data *data1, t_data *data2);
void	push(t_list **stack_a, t_list **stack_b, char stack_id);
void	swap(t_list **stack, char stack_id);
void	rotate(t_list **stack_a, t_list **stack_b, char stack_id);
void	rotate_reverse(t_list **stack_a, t_list **stack_b, char stack_id);
void	test_move_stack(void);
void	print_stack(t_list *stack);

t_data	*create_data(int value, int rank);
int		bit_count(int max);

#endif

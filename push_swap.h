/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:37:32 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/27 22:10:19 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct data
{
	int		value;
	int		rank;
}	t_data;

int	 	compare_rank(t_data *data1, t_data *data2);
void	push(t_list **stack_a, t_list **stack_b, char stack_id);
void	swap(t_list **stack, char stack_id);
void	rotate(t_list **stack_a, t_list **stack_b, char stack_id);
void	rotate_reverse(t_list **stack_a, t_list **stack_b, char stack_id);

int		bit_count(int max);

#endif

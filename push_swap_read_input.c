/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_read_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:28:09 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 15:30:31 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int duplicate(t_list *stack, int n)
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
		// ft_printf("aaa\n");
	}
	while (ac >= 2)
	{
		// ft_printf("bb\n");
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
		// for calc_rank, default rank is 0
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


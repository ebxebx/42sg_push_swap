/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:07:14 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 13:29:42 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_debug.h"
#include "stdarg.h"

void	debug_print_stack(t_list *stack, char *label)
{
	t_list	*current;
	t_data	*data;

	if (!DEBUG)
		return ;
	if (label && *label)
		ft_printf("%s", label);
	current = stack;
	while (current)
	{
		data = (t_data *)current->content;
		if (data)
			ft_printf("Value: %d, Rank: %d\n", data->value, data->rank);
		else
			ft_printf("Empty node\n");
		current = current->next;
	}
}

void	debug_printf(const char *format_str, ...)
{
	va_list	args;

	if (!DEBUG)
		return ;
	va_start(args, format_str);
	// Pass the format string AND the captured va_list to the target function pointer
	ft_vprintf(format_str, &args);
	va_end(args);
}

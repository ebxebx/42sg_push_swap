/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_debug.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:41:58 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/03 13:29:25 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_DEBUG_H
# define PUSH_SWAP_DEBUG_H

# include "push_swap.h"

void	debug_print_stack(t_list *stack, char *label);
void	debug_printf(const char *format_str, ...);

#endif

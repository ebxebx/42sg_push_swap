/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops_rot_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:58:29 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/02 19:03:11 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_ops.h"

void	rot_up(t_list **s)
{
	if (!(*s) || !(*s)->next)
		return ;
	ft_lstadd_back(s, ft_lstpop(s));
}

void	rot_down(t_list **s)
{
	t_list	*last;

	if (!(*s) || !(*s)->next)
		return ;
	last = ft_lstpop_back(s);
	ft_lstadd_front(s, last);
}

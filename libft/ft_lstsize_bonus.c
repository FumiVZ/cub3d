/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:22:20 by machrist          #+#    #+#             */
/*   Updated: 2024/09/25 18:18:22 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*tmp;

	len = 0;
	tmp = lst;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int	ft_lstlstsize(t_list **lst)
{
	int		len;
	t_list	*tmp;

	if (lst == NULL || *lst == NULL)
		return (0);
	len = 0;
	tmp = *lst;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

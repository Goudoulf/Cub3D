/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:19:13 by dvo               #+#    #+#             */
/*   Updated: 2024/05/31 16:14:37 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	free_lst_hero(t_list *hero)
{
	t_list	*tmp;
	t_list	*next;

	tmp = hero;
	if (hero != NULL)
	{
		next = tmp->next;
		free(tmp);
		hero = NULL;
		tmp = next;
		while (tmp != NULL)
		{
			next = tmp->next;
			free (tmp);
			tmp = next;
		}
		hero = NULL;
	}
	return (-1);
}

void	free_circular_list(t_list **list)
{
	t_list	*head;
	t_list	*temp;

	head = *list;
	temp = *list;
	while (temp->next != head)
		temp = temp->next;
	temp->next = NULL;
	temp = head;
	while (temp != NULL)
	{
		head = temp->next;
		free(temp);
		temp = head;
	}
	*list = temp;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:36:46 by wifons            #+#    #+#             */
/*   Updated: 2025/02/08 16:46:56 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	*g_clients = NULL;

t_client	*find_client(pid_t pid)
{
	t_client	*tmp;

	tmp = g_clients;
	while (tmp)
	{
		if (tmp->pid == pid)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_client	*create_client(pid_t pid)
{
	t_client	*new;

	new = malloc(sizeof(t_client));
	if (!new)
		return (NULL);
	new->pid = pid;
	new->bit_index = 0;
	new->char_index = 0;
	new->message = calloc(1024, sizeof(char));
	if (!new->message)
		return (free(new), NULL);
	new->next = g_clients;
	g_clients = new;
	return (new);
}

t_client	*get_client(pid_t pid, int addIfNotFound)
{
	t_client	*client;

	client = find_client(pid);
	if (!client && addIfNotFound)
		client = create_client(pid);
	return (client);
}

void	remove_client(pid_t pid)
{
	t_client	**current;
	t_client	*to_delete;

	current = &g_clients;
	while (*current)
	{
		if ((*current)->pid == pid)
		{
			to_delete = *current;
			*current = (*current)->next;
			free(to_delete->message);
			free(to_delete);
			return ;
		}
		current = &((*current)->next);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:37:04 by wifons            #+#    #+#             */
/*   Updated: 2025/02/08 16:43:02 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	update_character(int sig, t_client *client, unsigned char *c)
{
	*c |= (sig == BIT_1) << (7 - client->bit_index);
	client->bit_index++;
}

void	expand_buffer(t_client *client)
{
	char	*new_message;
	int		new_size;

	new_size = client->char_index + 1024;
	new_message = realloc(client->message, new_size);
	if (!new_message)
		return (remove_client(client->pid));
	client->message = new_message;
}

void	process_character(t_client *client, unsigned char character)
{
	if (character == '\0')
	{
		printf("[PID %d]: %s\n", client->pid, client->message);
		notify_process(client->pid, MESSAGE_CONFIRMED);
		client->char_index = 0;
	}
	else
	{
		if (client->char_index % 1024 == 0)
			expand_buffer(client);
		client->message[client->char_index++] = character;
		client->message[client->char_index] = '\0';
	}
}

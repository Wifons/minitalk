/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:11:56 by wifons            #+#    #+#             */
/*   Updated: 2025/02/08 16:46:25 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 200809L
# define _DEFAULT_SOURCE
# define _XOPEN_SOURCE 500
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define BIT_1 SIGUSR2
# define BIT_0 SIGUSR1
# define SERVER_READY SIGUSR1
# define MESSAGE_CONFIRMED SIGUSR2

// Structure pour stocker les clients actifs
typedef struct s_client
{
	pid_t				pid;
	char				*message;
	int					bit_index;
	int					char_index;
	struct s_client		*next;
}	t_client;

void			notify_process(pid_t pid, int sig);
t_client		*find_client(pid_t pid);
t_client		*create_client(pid_t pid);
t_client		*get_client(pid_t pid, int addIfNotFound);
void			remove_client(pid_t pid);
void			update_character(int sig, t_client *client, unsigned char *c);
void			expand_buffer(t_client *client);
void			process_character(t_client *client, unsigned char character);

#endif
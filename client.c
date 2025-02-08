/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:11:40 by wifons            #+#    #+#             */
/*   Updated: 2025/02/08 16:43:08 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_status = 0;

void	handle_ack(int sig)
{
	if (sig == SERVER_READY)
		g_status |= 1;
	else if (sig == MESSAGE_CONFIRMED)
		g_status |= 2;
}

void	send_char(pid_t server_pid, unsigned char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_status &= ~1;
		if ((c >> (7 - bit) & 1))
			notify_process(server_pid, BIT_1);
		else
			notify_process(server_pid, BIT_0);
		while (!(g_status & 1))
			usleep(50);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				server_pid;
	int					i;

	if (argc != 3)
		return (printf("Usage: %s <server_pid> <message>\n", argv[0]),
			EXIT_FAILURE);
	server_pid = atoi(argv[1]);
	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	i = 0;
	while (argv[2][i])
		send_char(server_pid, argv[2][i++]);
	send_char(server_pid, '\0');
	while (!(g_status & 2))
		usleep(50);
	printf("Message sent successfully!\n");
	return (EXIT_SUCCESS);
}

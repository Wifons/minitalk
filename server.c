/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:11:43 by wifons            #+#    #+#             */
/*   Updated: 2025/02/08 16:43:03 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	character;
	t_client				*client;

	(void)context;
	client = get_client(info->si_pid, 1);
	if (!client)
		return ;
	update_character(sig, client, &character);
	if (client->bit_index == 8)
	{
		process_character(client, character);
		client->bit_index = 0;
		character = 0;
	}
	notify_process(client->pid, SERVER_READY);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

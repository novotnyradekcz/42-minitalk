/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:45:55 by rnovotny          #+#    #+#             */
/*   Updated: 2023/08/10 21:53:32 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	btoc(int sig, char *c)
{
	if (sig == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (sig == SIGUSR2)
		*c = (*c << 1);
}

void	shandler(int sig, siginfo_t *info, void *ctx)
{
	static int	pid;
	static int	i;
	static char	c;

	(void)ctx;
	pid = info.si_pid;
	btoc(sig, &c);
	if (++i == 8)
	{
		i == 0;
		if (!c)
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		ft_printf("%c", c);
		c = 0;
	}
	kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Process ID: %d\n", getpid());
	// handle error
 	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = shandler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}

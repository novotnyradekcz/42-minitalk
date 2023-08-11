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

static void	ft_special(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	if (n == 0)
		write(fd, "0", 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	buf[10];
	int		i;
	int		neg;

	i = 0;
	neg = 0;
	ft_special(n, fd);
	if (n < 0 && n != -2147483648)
	{
		n = -n;
		neg = 1;
	}
	while (n > 0)
	{
		buf[i] = n % 10 + 48;
		n = n / 10;
		i++;
	}
	if (neg)
		write(fd, "-", 1);
	while (i > 0)
	{
		i--;
		write(fd, &buf[i], 1);
	}
}

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
	pid = info->si_pid;
	btoc(sig, &c);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	
	write(1, "Process ID: ", 13);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 2);
 	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = shandler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}

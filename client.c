/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:45:42 by rnovotny          #+#    #+#             */
/*   Updated: 2023/08/10 21:55:57 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	status;

int	ft_atoi(const char *nptr)
{
	int				i;
	int				neg;
	unsigned int	res;

	neg = 1;
	res = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -neg;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (neg * res);
}

int checkin(int checked, int checker)
{
	if (checker == 0 && checked != 3)
	{
		write(2, "Wrong input.\nShould be: ./client <PID> <message>\n", 50);
		return (1);
	}
	if (checker == 1 && kill(checked, 0) == -1)
	{
		write(2, "Invalid process ID\n", 20);
		return (1);
	}
	return (0);
}

void	shandler(int sig, siginfo_t *info, void *ctx)
{
	static int	i;

	(void)info;
	(void)ctx;
	status = 1;
	if (sig == SIGUSR2)
		i++;
	else if (sig == SIGUSR1)
	{
		// ft_printf("%d bytes received\n", i / 8);
		write(1, "Message received.\n", 19);
		exit(0);
	}
}

int	ctob(char c, int pid)
{
	int	i;
	int	j;

	i = 7;
	while (i >= 0)
	{
		j = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (status == 0)
		{
			if (j == 42)
			{
				write(1, "Server not responding.\n", 24);
				exit(1);
			}
			j++;
			usleep(100);
		}
		status = 0;
		i--;
	}
	return (0);
}

int main(int argc, char **argv)
{
	struct sigaction	sa;
	unsigned int		i;
	int					pid;

	if (checkin(argc, 0))
		return (1);
	pid = ft_atoi(argv[1]);
	if (checkin(pid, 1))
		return (1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = shandler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	i = 0;
	while (argv[2][i])
	{
		ctob(argv[2][i], pid);
		i++;
	}
	ctob('\0', pid);
}
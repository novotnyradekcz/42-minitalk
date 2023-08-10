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

void	shandler(int sig, siginfo_t *info, void *ctx)
{
	static int	i;

	(void)info;
	(void)ctx;
	counter = 1;
	if (sig == SIGUSR2)
		i++;
	else if (sig == SIGUSR1)
		ft_printf("%d bytes received\n", i / 8);
}

int	ctob(char c, int pid)
{
	int	i;
	int	j;

	i = 0;
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
				ft_printf("Server not responding.\n");
				return (1);
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
	char				i;
	int					pid;

	if (argc != 3)
	{
		ft_printf("Incorrect arguments.\n");
		ft_printf("Should be: ./client <PID> <message>\n");
	}
	pid = ft_atoi(argv[1]);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = shandler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// handle error
	i = 0;
	while (argv[2][i])
	{
		ctob(argv[2][i], pid);
		i++;
	}
	ctob('\0', pid);
}
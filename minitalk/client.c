/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:08:11 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/12/11 03:37:26 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int		res;
	size_t	i;
	size_t	sign;

	i = 0;
	sign = 0;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - 48;
		i++;
	}
	if (sign == 1)
		return (-res);
	return (res);
}

void	sigsend(int pid, char *s)
{
	int		i;
	int		bit;
	int		res;

	i = 0;
	res = 1;
	while (s[i])
	{
		bit = 7;
		while (bit >= 0)
		{
			if ((s[i] >> bit) & 1)
				res = kill(pid, SIGUSR1);
			else
				res = kill(pid, SIGUSR2);
			usleep(100);
			--bit;
		}
		++i;
	}
	if (res >= 0)
		write(1, "recived\n", 8);
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		sigsend(ft_atoi(argv[1]), argv[2]);
	return (0);
}

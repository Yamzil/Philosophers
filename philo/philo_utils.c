/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:48:18 by yamzil            #+#    #+#             */
/*   Updated: 2022/06/23 22:13:34 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_simulationoff(t_sh *share, pthread_t *philos, t_ph *philo)
{
	int	i;

	i = 0;
	while (i < share->ph_num)
		pthread_mutex_destroy(&share->forks[i++]);
	pthread_mutex_destroy(&share->print);
	free(share->forks);
	free(share);
	free(philo);
	free(philos);
	return (0);
}

void	ft_sleep(long long time)
{
	long long	expected_time;
	long long	temp_time;

	expected_time = ft_time() + time;
	temp_time = ft_time();
	while (temp_time < expected_time)
	{
		usleep(100);
		temp_time = ft_time();
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	i = 0;
	s11 = (unsigned char *) s1;
	s22 = (unsigned char *) s2;
	while (s11[i] != '\0' || s22[i] != '\0')
	{
		if (s11[i] != s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	n;

	i = 0;
	sign = 1;
	n = 0;
	if (!ft_strcmp(str, ""))
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] && !(str[i] >= '0' && str[i] <= '9'))
		return (0);
	if (((n * sign) > 2147483647) || ((n * sign) < -2147483648))
		return (0);
	return (n * sign);
}

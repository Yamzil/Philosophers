/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:47:23 by yamzil            #+#    #+#             */
/*   Updated: 2022/06/23 22:13:09 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long 	ft_time(void)
{
	long long			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	eating(t_ph *ph)
{
	pthread_mutex_lock(&ph->share->forks[ph->id % ph->share->ph_num]);
	pthread_mutex_lock(&ph->share->print);
	printf("%lld %d has taken a fork\n",
		(ft_time() - ph->share->time_start), ph->id);
	pthread_mutex_unlock(&ph->share->print);
	pthread_mutex_lock(&ph->share->forks[ph->id - 1]);
	pthread_mutex_lock(&ph->share->print);
	printf("%lld %d has taken a fork\n",
		(ft_time() - ph->share->time_start), ph->id);
	pthread_mutex_unlock(&ph->share->print);
	pthread_mutex_lock(&ph->share->print);
	printf("%lld %d is eating\n",
		(ft_time() - ph->share->time_start), ph->id);
	if (ph->meal_count > 0)
		ph->meal_count--;
	pthread_mutex_unlock(&ph->share->print);
	ph->last_meal = ft_time();
	ph->is_eating = 0;
	ft_sleep(ph->share->t_eat);
	ph->is_eating = 1;
	pthread_mutex_unlock(&ph->share->forks[ph->id - 1]);
	pthread_mutex_unlock(&ph->share->forks[ph->id % ph->share->ph_num]);
}

void	*ft_routine(void *data)
{
	t_ph	*ph;

	ph = (t_ph *)data;
	if (ph->id % 2 == 1)
		usleep(500);
	while (1)
	{
		eating(ph);
		pthread_mutex_lock(&ph->share->print);
		printf("%lld %d is sleeping\n",
			(ft_time() - ph->share->time_start), ph->id);
		pthread_mutex_unlock(&ph->share->print);
		ft_sleep(ph->share->t_sleep);
		pthread_mutex_lock(&ph->share->print);
		printf("%lld %d is thinking\n",
			(ft_time() - ph->share->time_start), ph->id);
		pthread_mutex_unlock(&ph->share->print);
	}
	return (ph);
}

int	check_dead(t_sh *share, t_ph *philo)
{
	int	i;
	int	count;

	while (1)
	{
		i = 0;
		count = 0;
		while (i < share->ph_num)
		{
			if ((ft_time() - philo[i].last_meal > share->t_die)
				&& philo[i].is_eating)
			{
				pthread_mutex_lock(&share->print);
				printf("%lld %d died\n",
					(ft_time() - share->time_start), philo[i].id);
				return (1);
			}
			count += philo[i].meal_count;
			i++;
		}
		if (count == 0)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_sh		*share;
	pthread_t	*philos;
	t_ph		*philo;
	int			i;

	i = 0;
	if (ac < 5 || ac > 6 || !ft_checkargs(av))
		return (1);
	share = malloc(sizeof(t_sh));
	if (ft_initialization(&share, av))
		return (1);
	philo = malloc(sizeof(t_ph) * share->ph_num);
	share->time_start = ft_time();
	philo = ft_init(philo, share);
	philos = malloc(sizeof(pthread_t) * share->ph_num);
	while (i < share->ph_num)
	{
		if (pthread_create(&philos[i], NULL, ft_routine, &philo[i]))
			return (1);
		pthread_detach(philos[i]);
		i++;
	}
	if (check_dead(share, philo))
		return (ft_simulationoff(share, philos, philo));
}
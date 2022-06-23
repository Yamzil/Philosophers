/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsingandinit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:45:59 by yamzil            #+#    #+#             */
/*   Updated: 2022/06/23 22:13:27 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_zero(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] != '0')
		return (0);
	while (str[i])
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_checkargs(char **av)
{
	int	i;

	i = 1;
	if (!av[i])
	{
		write(2, "Invalid argument\n", 17);
		return (0);
	}
	while (av[i])
	{
		if (is_zero(av[i]))
			i++;
		if (!av[i])
			break ;
		if (!ft_atoi(av[i]))
		{
			write(2, "Invalid argument\n", 16);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_initialization(t_sh **share, char **av)
{
	int	i;

	i = 0;
	(*share)->ph_num = ft_atoi(av[1]);
	(*share)->t_die = ft_atoi(av[2]);
	(*share)->t_eat = ft_atoi(av[3]);
	(*share)->t_sleep = ft_atoi(av[4]);
	if (av[5])
		(*share)->meat = ft_atoi(av[5]);
	else
		(*share)->meat = -1;
	(*share)->forks = malloc (sizeof(pthread_mutex_t) * (*share)->ph_num);
	while (i < (*share)->ph_num)
	{
		if (pthread_mutex_init(&(*share)->forks[i], NULL))
			return (1);
		i++;
	}
	pthread_mutex_init(&(*share)->print, NULL);
	return (0);
}

t_ph	*ft_init(t_ph *philo, t_sh *share)
{
	int	i;

	i = 0;
	while (i < share->ph_num)
	{
		philo[i].id = i + 1;
		philo[i].share = share;
		philo[i].last_meal = share->time_start;
		philo[i].meal_count = share->meat;
		philo[i].is_eating = 1;
		i++;
	}
	return (philo);
}

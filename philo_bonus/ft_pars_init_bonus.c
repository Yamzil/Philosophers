/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_init_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 23:06:26 by yamzil            #+#    #+#             */
/*   Updated: 2022/06/23 23:06:49 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

long long	ft_time(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
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
	(*share)->time_start = ft_time();
	return (0);
}

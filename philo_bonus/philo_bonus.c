/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:15:16 by yamzil            #+#    #+#             */
/*   Updated: 2022/06/23 23:09:03 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	*check_death(void *ar)
{
	t_ph	*philo;

	philo = (t_ph *) ar;
	usleep(500);
	while (1)
	{
		if (ft_time() - philo->last_meal > philo->share->t_die && philo->is_eating)
		{
			sem_wait(philo->share->print);
			printf("%lld %d died\n",
				(ft_time() - philo->share->time_start), philo->ph_id);
			exit(0);
		}
		if (philo->share->meat == 0)
			exit(1);
	}
	return (philo);
}

void	is_eating(t_ph **philo)
{
	sem_wait((*philo)->share->forks);
	sem_wait((*philo)->share->print);
	printf("%lld %d has taken a fork\n",
		(ft_time() - (*philo)->share->time_start), (*philo)->ph_id);
	sem_post((*philo)->share->print);
	sem_wait((*philo)->share->forks);
	sem_wait((*philo)->share->print);
	printf("%lld %d has taken a fork\n",
		(ft_time() - (*philo)->share->time_start), (*philo)->ph_id);
	sem_post((*philo)->share->print);
	sem_wait((*philo)->share->print);
	printf("%lld %d is eating\n",
		(ft_time() - (*philo)->share->time_start), (*philo)->ph_id);
	sem_post((*philo)->share->print);
	(*philo)->last_meal = ft_time();
	(*philo)->is_eating = 0;
	ft_sleep((*philo)->share->t_eat);
	(*philo)->is_eating = 1;
	sem_post((*philo)->share->forks);
	sem_post((*philo)->share->forks);
	if ((*philo)->share->meat > 0)
		(*philo)->share->meat--;
}

void	routine(t_ph **philo)
{
	if ((*philo)->ph_id % 2 == 1)
		usleep(500);
	while ((*philo)->share->meat != 0)
	{
		is_eating(philo);
		sem_wait((*philo)->share->print);
		printf("%lld %d is sleeping\n",
			(ft_time() - (*philo)->share->time_start), (*philo)->ph_id);
		sem_post((*philo)->share->print);
		ft_sleep((*philo)->share->t_sleep);
		sem_wait((*philo)->share->print);
		printf("%lld %d is thinking\n",
			(ft_time() - (*philo)->share->time_start), (*philo)->ph_id);
		sem_post((*philo)->share->print);
	}
}

int	*start_routine(t_sh *share, t_ph *philo, int *p_id)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < share->ph_num)
	{
		p_id[i] = fork();
		if (p_id[i] == 0)
		{
			philo->share = share;
			philo->last_meal = ft_time();
			philo->is_eating = 1;
			pthread_create(&thread, NULL, check_death, philo);
			pthread_detach(thread);
			routine(&philo);
		}
		i++;
		philo->ph_id++;
	}
	return (p_id);
}

int	main(int ac, char **av)
{
	t_sh		*share;
	t_ph		*philo;
	int			*p_id;

	if (ac < 5 || ac > 6 || !ft_checkargs(av))
		return (1);
	share = malloc (sizeof(t_sh));
	ft_initialization(&share, av);
	p_id = malloc(sizeof(int) * share->ph_num);
	philo = malloc (sizeof(t_ph));
	philo->ph_id = 1;
	sem_unlink("/forks");
	sem_unlink("/print");
	share->forks = sem_open("/forks", O_CREAT, S_IRUSR | S_IWUSR, share->ph_num);
	share->print = sem_open("/print", O_CREAT, S_IRUSR | S_IWUSR, 1);
	p_id = start_routine(share, philo, p_id);
	ft_clean_exit(p_id, share);
	return (ft_clean(share, philo, p_id));
}

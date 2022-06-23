/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:09:02 by yamzil            #+#    #+#             */
/*   Updated: 2022/06/23 22:13:18 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_sh{
	int				ph_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meat;
	long long		time_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_sh;

typedef struct s_ph{
	int			id;
	long long 	last_meal;
	t_sh		*share;
	int			meal_count;
	int			is_eating;
}	t_ph;

int			ft_checkargs(char **av);
int			ft_atoi(char *str);
int			ft_initialization(t_sh **share, char **av);
long long	ft_time(void);
t_ph		*ft_init(t_ph *data, t_sh *share);
void		ft_sleep(long long time);
int			ft_simulationoff(t_sh *share, pthread_t *philos, t_ph *philo);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:57:37 by yamzil            #+#    #+#             */
/*   Updated: 2022/06/23 23:09:37 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_sh
{
	int				ph_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meat;
	long long		time_start;
	sem_t			*forks;
	sem_t			*print;
}	t_sh;

typedef struct s_ph
{
	int			ph_id;
	long long	last_meal;
	t_sh		*share;
	int			is_eating;
}	t_ph;

int			ft_checkargs(char **av);
int			ft_initialization(t_sh **share, char **av);
int			ft_atoi(char *str);
int			ft_strcmp(char *s1, char *s2);
long long 	ft_time(void);
void		ft_sleep(long long time);
int			ft_clean(t_sh *share, t_ph *philo, int *p_id);
void		ft_clean_exit(int	*id, t_sh *share);

#endif
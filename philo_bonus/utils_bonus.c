/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:26:42 by yamzil            #+#    #+#             */
/*   Updated: 2022/06/23 23:10:51 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	ft_clean(t_sh *share, t_ph *philo, int *p_id)
{
	free(share);
	free(p_id);
	free(philo);
	return (0);
}

void	ft_clean_exit(int	*id, t_sh *share)
{
	int	i;
	int	p_id;
	int	stat;

	p_id = waitpid(-1, &stat, 0);
	i = 0;
	if (stat == 0)
	{	
		while (i < share->ph_num)
		{
			if (id[i] == p_id)
				i++;
			kill(id[i], 2);
			i++;
		}
	}
	else
		while (++i < share->ph_num)
			waitpid(-1, NULL, 0);
	sem_close(share->forks);
	sem_close(share->print);
	sem_unlink("/forks");
	sem_unlink("/print");
	exit(0);
}

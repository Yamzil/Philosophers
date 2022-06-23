/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:41:58 by yamzil            #+#    #+#             */
/*   Updated: 2022/06/23 23:01:20 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	s3;
	unsigned char	s4;
	int				i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		s3 = s1[i];
		s4 = s2[i];
		if (s3 != s4)
			return (s3 - s4);
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

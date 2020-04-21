/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 15:18:53 by user42            #+#    #+#             */
/*   Updated: 2020/04/21 15:20:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int			res;
	int			neg;

	res = 0;
	neg = 1;
	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v' ||
	*nptr == '\f' || *nptr == '\r' || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		neg = -neg;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9' && *nptr != '\0')
	{
		res = (res * 10) + (*nptr - 48);
		nptr++;
	}
	return (res * neg);
}

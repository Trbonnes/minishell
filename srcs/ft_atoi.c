/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:29:13 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:29:14 by trbonnes         ###   ########.fr       */
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

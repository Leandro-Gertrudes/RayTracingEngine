/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:32:28 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/11/30 17:32:28 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'
			|| str[*i] == '\v' || str[*i] == '\f' || str[*i] == '\r'))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static double	parse_decimal(const char *str)
{
	double	divisor;
	double	dec;
	int		i;

	dec = 0;
	divisor = 1;
	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		dec = dec * 10 + (str[i] - '0');
		divisor *= 10;
		i++;
	}
	return (dec / divisor);
}

double	ft_atod(const char *str)
{
	double	result;
	int		i;
	int		sign;

	i = 0;
	result = 0;
	if (!str)
		return (0);
	sign = get_sign(str, &i);
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		result += parse_decimal(&str[i + 1]);
	return (result * sign);
}

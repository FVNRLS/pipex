/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_dec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:52:13 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 11:47:06 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*
	Func. takes a number as input and calculates a value (size), which is going
	to be used for memory allocation for the function: ft_printint
	The size predetermines the length of the str. created in itoa conversion.
	Divident value: 10
*/
size_t	ft_count_size_dec(int n)
{	
	int	size;

	if (n == 0)
	{
		size = 1;
		return (size);
	}
	size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

/*
	Conversion from int into decimal values.
	The values are stored in a string (usage of memory allocation).
	Return value: pointer to the created string.
*/
char	*ft_itoa_dec(int n)
{
	char	*str;
	long	nbr;
	size_t	size;

	nbr = n;
	if (nbr < 0)
		nbr *= -1;
	size = ft_count_size_dec(nbr);
	str = (malloc(sizeof(char) * (size) + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
		size--;
	while (nbr > 0)
	{
		str[size] = (nbr % 10) + '0';
		nbr /= 10;
		size--;
	}
	if (size == 0 && str[1] == '\0')
		str[0] = '0';
	return (str);
}

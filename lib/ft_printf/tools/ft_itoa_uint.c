/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:49:34 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 19:38:30 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*
	Func. takes a number as input and calculates a value (size), which is going
	to be used for memory allocation for the function: ft_print_uint
	The size predetermines the length of the str. created in itoa conversion.
	Divident value: 10
*/
size_t	ft_count_size_uint(unsigned int n)
{	
	int	size;

	size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

/*
	Conversion from unsigned int into decimal values.
	The values are stored in a string (usage of memory allocation).
	Return value: pointer to the created string.
*/
char	*ft_itoa_uint(unsigned int nbr)
{
	char	*str;
	size_t	size;

	if (nbr == 0)
	{
		str = (malloc(sizeof(char) * 2));
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	size = ft_count_size_uint(nbr);
	str = (malloc(sizeof(char) * (size + 1)));
	if (!str)
		return (NULL);
	str[size] = '\0';
		size--;
	while (nbr > 0)
	{
		str[size] = nbr % 10 + '0';
		nbr /= 10;
		size--;
	}
	return (str);
}

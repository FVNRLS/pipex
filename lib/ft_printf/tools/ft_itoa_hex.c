/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:09:17 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/20 13:59:24 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*
	Func. takes a number as input and calculates a value (size), which is going
	to be used for memory allocation for the following functions:
	- ft_itoa_hex()
	- ft_itoa_ptr()
	The size predetermines the length of the str. created in itoa conversion.
	Divident value: 16
*/
size_t	ft_count_size_hex(unsigned long n, t_mod *mods)
{	
	int	size;

	size = 0;
	while (n > 0)
	{
		size++;
		n /= 16;
	}
	if (size > 8 && mods->is_ptr == 0)
		size = 8;
	return (size);
}

/*
	Conversion from unsigned long into hexadecimal values.
	The values are stored in a string (usage of memory allocation).
	The values can be upper -or lowercase, depending on the conversion spec.
	--> HEX_BASE_LOWERCASE or HEX_BASE_UPPERCASE (defined in ft_printf.h)
	Return value: pointer to the created string.
*/
char	*ft_itoa_hex(unsigned long n, t_mod *mods)
{
	char	*str;
	char	*hex_base;
	size_t	size;

	if (mods->spec == 'x')
		hex_base = HEX_BASE_LOWERCASE;
	else if (mods->spec == 'X')
		hex_base = HEX_BASE_UPPERCASE;
	size = ft_count_size_hex(n, mods);
	str = (malloc(sizeof(char) * (size + 1)));
	if (!str)
		return (NULL);
	str[size] = '\0';
		size--;
	while (n > 0)
	{
		str[size] = hex_base[n % 16];
		n /= 16;
		size--;
	}
	return (str);
}

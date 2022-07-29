/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:53:11 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/20 13:42:25 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*
	Conversion a pointer address from unsigned long into hexadecimal values.
	The values are stored in a string (usage of memory allocation).
	The values are always represented in lowercase format
	(usage of HEX_BASE_LOWERCASE).
	Return value: pointer to the created string.
*/
char	*ft_itoa_ptr(unsigned long n, t_mod *mods)
{
	char	*str;
	size_t	size;

	size = ft_count_size_hex(n, mods);
	if (n == 0)
	{
		str = (malloc(sizeof(char) * 2));
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	else
		str = (malloc(sizeof(char) * (size + 1)));
	if (!str)
		return (NULL);
	str[size] = '\0';
		size--;
	while (n > 0)
	{
		str[size--] = HEX_BASE_LOWERCASE[n % 16];
		n /= 16;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:57:21 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/20 14:13:30 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Conversion of a number to hexadecimal value.
	Input values are initially converted to unsigned long (via va_arg input).
	Limits: LONG_MIN 	-->		print value:	0
			LONG_MAX 	-->		print value:	ffffffff
			ULONG_MAX	-->		print value:	ffffffff
	LONG_MAX and ULONG_MAX are handled via 'if (len > 8)' check
	If the number is not out of the limits range, mods are going to be applied. 
*/

void	ft_printhex(t_input *input, t_mod *mods)
{
	unsigned long	nbr;
	char			*str;
	int				len;

	nbr = (unsigned long)va_arg(input->arg, unsigned int);
	str = ft_itoa_hex(nbr, mods);
	if ((long)nbr == LONG_MIN || nbr == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	len = ft_strlen(str);
	ft_apply_mods(input, mods, str, len);
	free(str);
	str = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:20:01 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 14:22:06 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Converts the input number to decimal value.
	Input values are initially converted to unsigned int (via va_arg input).
	Limits: ULONG_MAX
	If the number is not out of the limits range, mods are going to be applied. 
*/
void	ft_print_uint(t_input *input, t_mod *mods)
{
	unsigned long	nbr;
	char			*str;
	char			len;

	nbr = va_arg(input->arg, unsigned int);
	str = ft_itoa_uint(nbr);
	len = ft_strlen(str);
	ft_apply_mods(input, mods, str, len);
	free(str);
	str = NULL;
}

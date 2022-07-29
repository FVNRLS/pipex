/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:01:38 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/20 13:41:30 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
	Conversion of a number to hexadecimal value.
	Takes void*-formatted pointer address as input argument.
	Input values are initially converted to unsigned long (via va_arg input).
	Ajusts and applies mods. 
	NULL-Pointers are represented with 0x0.
*/
void	ft_printptr(t_input *input, t_mod *mods)
{
	unsigned long	ptr;
	char			*str;
	int				len;

	mods->is_ptr = 1;
	ptr = (unsigned long)va_arg(input->arg, void *);
	str = ft_itoa_ptr(ptr, mods);
	len = ft_strlen(str);
	ft_apply_mods(input, mods, str, len);
	free(str);
	str = NULL;
}

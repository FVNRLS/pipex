/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:39:30 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 14:26:05 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Converts the input number to decimal value.
	Input values are initially converted to char* (via va_arg input).
	Ajusts and applies mods and prints the string to stdout.
	If input is NULL, then str value is (null) (6 characters). 
*/
void	ft_printstr(t_input *input, t_mod *mods)
{
	char	*str;
	int		len;

	mods->is_string = 1;
	str = va_arg(input->arg, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	ft_apply_mods(input, mods, str, len);
}

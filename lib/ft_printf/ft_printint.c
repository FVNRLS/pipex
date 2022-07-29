/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:43:55 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 14:24:36 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Conversion of a number to hexadecimal value.
	Input values are initially converted to int (via va_arg input).
	Limits: INT_MIN and INT_MAX.
	Exception rule: 
	If the number is 0 and 0-precision is set, it's not going to be printed.
	If the number is not out of the limits range, mods are going to be applied. 
*/
void	ft_printint(t_input *input, t_mod *mods)
{
	int		nbr;
	char	*str;
	int		len;

	nbr = va_arg(input->arg, int);
	if (nbr < 0)
	{
		mods->is_negative = 1;
		mods->plus = 0;
	}
	str = ft_itoa_dec(nbr);
	len = ft_strlen(str);
	if (mods->prec == 1 && mods->pads == 0 && nbr == 0 && mods->prec_pads == 0)
	{
		free(str);
		str = NULL;
		return ;
	}		
	ft_apply_mods(input, mods, str, len);
	free(str);
	str = NULL;
}

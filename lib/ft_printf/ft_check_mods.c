/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_mods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:12:19 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 14:19:10 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check_precision(t_mod *mods)
{
	if (ft_isdigit(mods->spec) == 1)
	{
		mods->width = 1;
		if (mods->pads != 0)
			mods->pads *= 10;
		mods->pads += (mods->spec - '0');
	}
	if (mods->spec == '.')
	{
		mods->prec = 1;
		mods->prec_pads = mods->pads;
		mods->width = 0;
		mods->pads = 0;
	}
}

/*
	Order prototype:
	%[flags][width][.precision][.length]specifier
	Check all format modifiers and set the flag to 1 if true.
	Check the precision and convert numbers after '.' sign to precision pads 
	and normal pads.
*/
void	ft_check_mods(t_input *input, t_mod *mods)
{
	mods->spec = input->format[input->pos];
	if (mods->spec == '0' && (ft_isdigit(input->format[input->pos - 1]) == 0)
		&& ft_isdigit(input->format[input->pos + 1]) == 1)
		mods->zero = 1;
	if (mods->spec == '+')
		mods->plus = 1;
	if (mods->spec == '-')
		mods->minus = 1;
	if (mods->spec == ' ')
		mods->space = 1;
	if (mods->spec == '#')
		mods->hash = 1;
	ft_check_precision(mods);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_prefix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:52:55 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 14:00:33 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_apply_signs(t_input *input, t_mod *mods)
{
	if (mods->space == 1)
	{
		write(1, " ", 1);
		mods->space = 0;
		input->ret_nbr++;
	}
	if (mods->plus == 1)
	{
		write(1, "+", 1);
		mods->plus = 0;
		input->ret_nbr++;
	}
	if (mods->is_negative == 1)
	{
		write(1, "-", 1);
		mods->is_negative = 0;
		input->ret_nbr++;
	}
}

/*
	Adds a prefix for conversion specs:		'x', 'X' and 'p'
	Applies conversion mods:				' ', '-' and '+'
*/
void	ft_apply_prefix(t_input *input, t_mod *mods, char *str)
{
	if (mods->is_ptr == 1)
	{
		write(1, "0x", 2);
		input->ret_nbr += 2;
	}
	else if (str[0] != '0')
	{
		if (mods->hash == 1)
		{
			if (mods->spec == 'x')
				write(1, "0x", 2);
			else if (mods->spec == 'X')
				write(1, "0X", 2);
		input->ret_nbr += 2;
		}
	}
	ft_apply_signs(input, mods);
}

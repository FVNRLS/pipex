/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_convert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 17:26:43 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 14:21:07 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Initialize all conversion modifiers flags to 0.
	Function is applied before every new parsing.
	For every new argument the flags are nulled.
*/
void	ft_init_mods(t_mod *mods)
{
	mods->zero = 0;
	mods->plus = 0;
	mods->minus = 0;
	mods->space = 0;
	mods->hash = 0;
	mods->width = 0;
	mods->prec = 0;
	mods->spec = 0;
	mods->pads = 0;
	mods->prec_pads = 0;
	mods->is_string = 0;
	mods->is_ptr = 0;
	mods->is_negative = 0;
}

/*
	Checks the conversion specifiers and applies the particular conversion.
*/
void	ft_convert(t_input *input, t_mod *mods)
{
	mods->spec = input->format[input->pos];
	if (mods->spec == 'c' || mods->spec == '%')
		ft_printchar(input, mods);
	else if (mods->spec == 's')
		ft_printstr(input, mods);
	else if (mods->spec == 'i' || mods->spec == 'd')
		ft_printint(input, mods);
	else if (mods->spec == 'p')
		ft_printptr(input, mods);
	else if (mods->spec == 'x' || mods->spec == 'X')
		ft_printhex(input, mods);
	else if (mods->spec == 'u')
		ft_print_uint(input, mods);
}

/*
	Core function.
	Cheks the total input of ft_printf char by char and searches for %-sign.
	If no % sign is found --> prints the char to stdout.
	If % sign is found --> cheks format modifier is valid with ALL_SYMBOLS.
	If valid:
		1. Checks with FORM_MODS and modifies the flags.
		2. Checks for format specs with FORM_SPECS and converts the argument.
		3. Sets the mods flags back to 0.	
*/
void	ft_parse(t_input *input, t_mod *mods)
{
	while (input->format[input->pos])
	{
		if (input->format[input->pos] != '%')
			input->ret_nbr += write(1, input->format + input->pos, 1);
		else if (ft_strchr(ALL_SYMBOLS, input->format[input->pos + 1]))
		{
			input->pos++;
			while (ft_strchr(FORM_MODS, input->format[input->pos]))
			{
				ft_check_mods(input, mods);
				input->pos++;
			}
			if (ft_strchr(FORM_SPECS, input->format[input->pos]))
				ft_convert(input, mods);
			ft_init_mods(mods);
		}
		input->pos++;
	}
}

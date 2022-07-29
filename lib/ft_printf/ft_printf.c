/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:48:47 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 14:23:29 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Initializes flags from t_input to 0.
*/
static void	ft_init_input(t_input *input, const char *format, va_list arg)
{
	input->format = format;
	va_copy(input->arg, arg);
	input->ret_nbr = 0;
	input->pos = 0;
}

/*
	Processes arguments one by one:
	Processes argument to the struct and initialize the 2 structs and inits:
		- format mods to 0.
		- other flags (position, return number) to 0.
	Parses the arguments into the ft_parse function.
	Performs the actions until (incl.) the last argument.
	Returns the total number of printed characters.
	
*/
int	ft_printf(const char *format, ...)
{
	va_list	arg;
	t_mod	mods;
	t_input	input;

	va_start(arg, format);
	ft_init_input(&input, format, arg);
	ft_init_mods(&mods);
	ft_parse(&input, &mods);
	va_end(arg);
	return (input.ret_nbr);
}

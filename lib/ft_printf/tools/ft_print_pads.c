/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:11:05 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 19:38:59 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*
	Precision pads are defined before the '.' sign.
	Space-sign will be printed so many times as the number of precision pads.
*/
void	ft_print_prec_pads(t_input *input, t_mod *mods)
{
	int	i;

	i = 0;
	while (i < mods->prec_pads)
	{
		write(1, " ", 1);
		i++;
		input->ret_nbr++;
	}
}

/*
	Zeropads pads should be used if '0' sign is activ (not nulled).
	The value of yeropads is always the value of the normal pads (mods->pads)
	0-sign will be printed so many times as the number of zeropads.
*/
void	ft_print_zeropads(t_input *input, t_mod *mods)
{
	int	i;

	i = 0;
	while (i < mods->pads)
	{
		write(1, "0", 1);
		i++;
		input->ret_nbr++;
	}
}

/*
	Normal pads are defined after the '.' sign or before the conversion spec. if
	no precision is set.
	The pads will be printed so many times as the number of mods->pads.
*/
void	ft_print_pads(t_input *input, t_mod *mods)
{
	int	i;

	i = 0;
	while (i < mods->pads)
	{
		write(1, " ", 1);
		i++;
		input->ret_nbr++;
	}
}

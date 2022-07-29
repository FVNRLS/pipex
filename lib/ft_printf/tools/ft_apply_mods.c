/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_mods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:39:33 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/20 20:23:09 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*
	Some conversion mods conflict with each other, so before applying, some of
	them should be ajusted (nulled).
	The function also preajusts the pads, depending on conversion spec.
*/
void	ft_ajust_mods(t_mod *mods)
{
	if (mods->width == 0)
		mods->minus = 0;
	if (mods->width == 0 || mods->prec == 1 || mods->minus == 1)
		mods->zero = 0;
	if (mods->pads == 0)
		mods->width = 0;
	if (mods->hash == 1 && mods->prec == 0)
		mods->pads -= 2;
	if (mods->is_negative == 1)
		mods->space = 0;
	if (mods->is_negative == 1 && mods->prec == 0)
		mods->pads--;
	if (mods->space == 1)
		mods->pads--;
	if (mods->plus)
		mods->pads--;
	if (mods->is_string == 1)
		mods->space = 0;
}

/*
	Ajusts the precision pads and normal pads (also zeropads), depending,
	whether there is a precision or not.
*/
void	ft_ajust_pads(t_mod *mods, char *str, int len)
{
	if (mods->is_string == 1 && mods->prec == 1)
	{
		if (mods->minus == 1 && mods->prec_pads > mods->pads)
			mods->prec_pads -= mods->pads;
		else if (mods->prec_pads > len)
			mods->prec_pads -= len;
		else if (mods->prec_pads < len && mods->prec_pads > mods->pads)
			mods->prec_pads -= mods->pads;
	}
	else if (mods->is_ptr == 1)
		mods->pads -= (len + 2);
	else if (mods->prec_pads == 0)
		mods->pads -= len;
	else if (mods->prec_pads > 0 && mods->is_string == 0)
	{
		if (mods->is_negative == 1)
			mods->prec_pads--;
		if (mods->prec_pads > mods->pads && mods->pads <= len && str[0] != '0')
			mods->prec_pads -= len;
		else
			mods->prec_pads -= mods->pads;
		mods->pads -= len;
	}
}

/*
	If precision mod is used, applies precision rules, depending on the
	conversion spec. and conversion mods.
	Applies the prefix, if used and prints the pads and the converted string
	to stdout.
*/
void	ft_apply_prec_mods(t_input *input, t_mod *mods, char *str)
{
	if (mods->is_string == 1)
	{	
		if (mods->minus == 0)
			ft_print_prec_pads(input, mods);
		ft_putstr(str, input, mods);
		if (mods->minus == 1)
			ft_print_prec_pads(input, mods);
	}	
	else if (mods->minus == 0 && mods->prec == 1)
	{
		ft_print_prec_pads(input, mods);
		ft_apply_prefix(input, mods, str);
		ft_print_zeropads(input, mods);
		ft_putstr(str, input, mods);
	}
	else if (mods->minus == 1 && mods->prec == 1)
	{	
		ft_apply_prefix(input, mods, str);
		ft_print_zeropads(input, mods);
		ft_putstr(str, input, mods);
		ft_print_prec_pads(input, mods);
	}
}

/*
	If no precision mod is used, applies the other depending on the
	conversion spec. and conversion mods.
	As last also includes a rule, if no mods are used at all.
	Applies the prefix, if used and prints the pads and the converted string
	to stdout.
*/
void	ft_apply_noprec_mods(t_input *input, t_mod *mods, char *str)
{	
	if (mods->minus == 1 && mods->prec == 0)
	{	
		ft_apply_prefix(input, mods, str);
		ft_putstr(str, input, mods);
		ft_print_pads(input, mods);
		return ;
	}
	if ((mods->hash || mods->plus || mods->space) && mods->width == 0)
		ft_apply_prefix(input, mods, str);
	if (mods->minus == 0 && mods->width && mods->zero == 0 && mods->prec == 0)
	{
		ft_print_pads(input, mods);
		ft_apply_prefix(input, mods, str);
	}
	if (mods->zero == 1 && mods->width == 1)
	{
		ft_apply_prefix(input, mods, str);
		ft_print_zeropads(input, mods);
	}
	if (mods->minus == 0 && mods->width == 0 && mods->zero == 0
		&& mods->hash == 0 && mods->space == 0 && mods->plus == 0)
		ft_apply_prefix(input, mods, str);
	ft_putstr(str, input, mods);
}

/*
	Invokes the functions above to check and apply all rules together.
*/
void	ft_apply_mods(t_input *input, t_mod *mods, char *str, int len)
{
	ft_ajust_mods(mods);
	ft_ajust_pads(mods, str, len);
	if (mods->prec == 1)
		ft_apply_prec_mods(input, mods, str);
	else if (mods->prec == 0)
		ft_apply_noprec_mods(input, mods, str);
}

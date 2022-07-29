/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:34:37 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 19:37:46 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"	

/*
	Prints the converted string, depending if precision flag is set or not. 
*/
void	ft_putstr(char *str, t_input *input, t_mod *mods)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (mods->is_string == 1 && mods->prec == 1)
		len = mods->pads;
	if (mods->prec == 1)
	{	
		if (mods->width == 0 && str[0] == '0')
			return ;
		while (i < len && str[i] != '\0')
		{
			write(1, &str[i++], 1);
			input->ret_nbr++;
		}
	}
	else if (mods->prec == 0)
	{
		while (str[i] != '\0')
		{
			write(1, &str[i++], 1);
			input->ret_nbr++;
		}
	}
}

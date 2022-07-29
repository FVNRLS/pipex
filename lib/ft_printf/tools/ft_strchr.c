/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:47:37 by rmazurit          #+#    #+#             */
/*   Updated: 2022/05/19 11:57:13 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*
	Searches for the first occurrence of the character c the string pointed 
	to by the argument s. 
	Returns a pointer to the first occurrence of the character c in the string 
	or NULL if the character is not found.
*/
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *) s + i);
		i++;
	}
	if (s[i] == c)
		return ((char *) s + i);
	else
		return (NULL);
}

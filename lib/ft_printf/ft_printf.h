/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:04:38 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/25 19:15:34 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# define FORM_SPECS			"cspdiouxX%%"
# define ALL_SYMBOLS		"cspdiouxX%%#-+ .*0123456789"
# define FORM_MODS			"#-+ .*0123456789"
# define HEX_BASE_LOWERCASE	"0123456789abcdef"
# define HEX_BASE_UPPERCASE	"0123456789ABCDEF"

typedef struct s_mod
{
	int		zero;
	int		plus;
	int		minus;
	int		space;
	int		hash;
	int		width;
	int		prec;	
	char	spec;
	int		pads;
	int		is_negative;
	int		prec_pads;
	int		is_string;
	int		is_ptr;
}			t_mod;

typedef struct s_input
{
	const char	*format;
	va_list		arg;
	size_t		ret_nbr;
	size_t		pos;
}				t_input;

//INIT AND PARSING
int		ft_printf(const char *format, ...);
void	ft_init_mods(t_mod *mods);
void	ft_parse(t_input *input, t_mod *mods);
void	ft_check_mods(t_input *input, t_mod *mods);

//CONVERSIONS
void	ft_convert(t_input *input, t_mod *mods);
void	ft_printchar(t_input *input, t_mod *mods);
void	ft_printstr(t_input *input, t_mod *mods);
void	ft_printint(t_input *input, t_mod *mods);
void	ft_printptr(t_input *input, t_mod *mods);
void	ft_printhex(t_input *input, t_mod *mods);
void	ft_print_uint(t_input *input, t_mod *mods);

//TOOLS
int		ft_isdigit(int c);
int		ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	ft_putstr(char *str, t_input *input, t_mod *mods);
void	ft_print_pads(t_input *input, t_mod *mods);
void	ft_print_zeropads(t_input *input, t_mod *mods);
void	ft_print_prec_pads(t_input *input, t_mod *mods);
char	*ft_itoa_dec(int n);
char	*ft_itoa_ptr(unsigned long n, t_mod *mods);
char	*ft_itoa_hex(unsigned long n, t_mod *mods);
char	*ft_itoa_uint(unsigned int nbr);
size_t	ft_count_size_hex(unsigned long n, t_mod *mods);
void	ft_apply_mods(t_input *input, t_mod *mods, char *str, int len);
void	ft_apply_prefix(t_input *input, t_mod *mods, char *str);

#endif

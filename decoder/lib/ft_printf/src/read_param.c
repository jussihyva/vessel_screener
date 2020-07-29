/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 17:54:26 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/29 18:24:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long		read_o_u_x_param(t_type type, va_list *ap)
{
	long long	nbr;

	if (type == hh)
		nbr = (unsigned char)(va_arg(*ap, unsigned int));
	else if (type == h)
		nbr = (unsigned short)(va_arg(*ap, unsigned int));
	else if (type == l)
		nbr = (unsigned long)(va_arg(*ap, void *));
	else if (type == ll)
		nbr = (unsigned long long)(va_arg(*ap, unsigned long long));
	else if (type == j)
		nbr = (uintmax_t)(va_arg(*ap, uintmax_t));
	else if (type == z)
		nbr = (size_t)(va_arg(*ap, void *));
	else if (type == t)
		nbr = (ptrdiff_t)(va_arg(*ap, void *));
	else if (type == L)
		nbr = (unsigned char)(va_arg(*ap, unsigned int));
	else
		nbr = (unsigned char)(va_arg(*ap, unsigned int));
	return (nbr);
}

long double		read_f_param(t_type type, va_list *ap)
{
	long double		nbr;

	if (type == hh)
		nbr = (double)(va_arg(*ap, double));
	else if (type == h)
		nbr = (double)(va_arg(*ap, double));
	else if (type == l)
		nbr = (double)(va_arg(*ap, double));
	else if (type == ll)
		nbr = (double)(va_arg(*ap, double));
	else if (type == j)
		nbr = (double)(va_arg(*ap, double));
	else if (type == z)
		nbr = (double)(va_arg(*ap, double));
	else if (type == t)
		nbr = (double)(va_arg(*ap, double));
	else if (type == L)
		nbr = (long double)(va_arg(*ap, long double));
	else
		nbr = (double)(va_arg(*ap, double));
	return (nbr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:24:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/10 10:14:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				set_int_parameter(t_substring *substring)
{
	char			*s;
	long long		par_value;

	par_value = *(long long *)substring->par_value;
	s = ft_lltoa_base(par_value, 10);
	if (par_value == 0 && substring->precision == 0)
	{
		save_parameter(substring, "");
		ft_strdel(&s);
	}
	else if (par_value < 0)
	{
		save_parameter(substring, ft_strdup(s + 1));
		ft_strdel(&s);
	}
	else
		save_parameter(substring, s);
	free(substring->par_value);
	substring->par_value = NULL;
	return ;
}

void					adjust_int(t_substring *substring)
{
	set_int_parameter(substring);
	set_sign(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
}

static long long		read_int_param(t_type type, va_list *ap)
{
	long long	nbr;

	if (type == hh)
		nbr = (char)(va_arg(*ap, int));
	else if (type == h)
		nbr = (short)(va_arg(*ap, int));
	else if (type == l)
		nbr = (long)(va_arg(*ap, void *));
	else if (type == ll)
		nbr = (long long)(va_arg(*ap, long long));
	else if (type == j)
		nbr = (intmax_t)(va_arg(*ap, intmax_t));
	else if (type == z)
		nbr = (size_t)(va_arg(*ap, void *));
	else if (type == t)
		nbr = (ptrdiff_t)(va_arg(*ap, void *));
	else if (type == L)
		nbr = (int)(va_arg(*ap, void *));
	else
		nbr = (int)(va_arg(*ap, void *));
	return (nbr);
}

char					*conv_int(va_list *ap, t_substring *substring,
											int *attrs)
{
	long long		*nbr;

	(*attrs)++;
	nbr = (long long *)ft_memalloc(sizeof(*nbr));
	if (!substring->param_type)
		*nbr = (int)(va_arg(*ap, void *));
	else
		*nbr = read_int_param(substring->param_type->type, ap);
	substring->par_value = nbr;
	if (*nbr < 0)
		substring->par_value_is_neg = 1;
	return (NULL);
}

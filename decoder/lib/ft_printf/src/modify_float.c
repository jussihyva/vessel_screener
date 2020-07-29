/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:01:45 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/09 17:36:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				set_double_parameter(t_substring *substring)
{
	int				add_dot;
	char			*s;
	long double		par_value;

	add_dot = substring->flags & hash;
	par_value = *(long double *)substring->par_value;
	s = ft_dtoa_base(par_value, 10, substring->precision, add_dot);
	if (substring->par_value_is_neg)
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

char					*conv_float(va_list *ap, t_substring *substring,
															int *attrs)
{
	long double		*nbr;

	(*attrs)++;
	nbr = (long double *)ft_memalloc(sizeof(*nbr));
	if (!substring->param_type)
		*nbr = (double)va_arg(*ap, double);
	else
		*nbr = read_f_param(substring->param_type->type, ap);
	if (substring->precision == -1)
		substring->precision = 6;
	substring->par_value = nbr;
	if (*nbr < 0)
		substring->par_value_is_neg = 1;
	return (NULL);
}

void					adjust_float(t_substring *substring)
{
	set_double_parameter(substring);
	set_sign(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
}

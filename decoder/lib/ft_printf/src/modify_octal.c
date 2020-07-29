/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_octal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:46:22 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/09 18:01:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				set_octal_parameter(t_substring *substring)
{
	char					*s;
	unsigned long long		par_value;

	par_value = *(unsigned long long *)substring->par_value;
	if (substring->flags & hash || par_value || substring->precision != 0)
	{
		s = ft_ulltoa_base(par_value, 8);
		save_parameter(substring, s);
	}
	else
		save_parameter(substring, "");
	free(substring->par_value);
	substring->par_value = NULL;
}

void					adjust_unsigned_octal(t_substring *substring)
{
	set_octal_parameter(substring);
	set_sign(substring);
	set_prefix(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
}

char					*conv_unsigned_octal(va_list *ap,
										t_substring *substring, int *attrs)
{
	unsigned long long		*nbr;

	(*attrs)++;
	nbr = (unsigned long long *)ft_memalloc(sizeof(*nbr));
	if (!substring->param_type)
		*nbr = (unsigned int)(va_arg(*ap, void *));
	else
		*nbr = read_o_u_x_param(substring->param_type->type, ap);
	substring->par_value = nbr;
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_unsigned_integer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:13:41 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/07 21:27:20 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				set_unsigned_int_parameter(t_substring *substring)
{
	char					*s;
	unsigned long long		par_value;

	par_value = *(unsigned long long *)substring->par_value;
	s = ft_ulltoa_base(par_value, 10);
	if (par_value == 0 && substring->precision == 0)
	{
		save_parameter(substring, "");
		ft_strdel(&s);
	}
	else
		save_parameter(substring, s);
	free(substring->par_value);
	substring->par_value = NULL;
	return ;
}

void					adjust_unsigned_int(t_substring *substring)
{
	set_unsigned_int_parameter(substring);
	set_sign(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
}

char					*conv_unsigned_int(va_list *ap,
										t_substring *substring, int *attrs)
{
	unsigned long long		*nbr;

	(*attrs)++;
	nbr = (unsigned long long *)ft_memalloc(sizeof(*nbr));
	if (!substring->param_type)
		*nbr = va_arg(*ap, unsigned int);
	else
		*nbr = read_o_u_x_param(substring->param_type->type, ap);
	substring->par_value = nbr;
	return (NULL);
}

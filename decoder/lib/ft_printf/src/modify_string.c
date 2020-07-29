/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:53:59 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/09 19:50:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		set_string_parameter(t_substring *substring)
{
	char			*s;

	s = (char *)substring->par_value;
	if (substring->precision >= 0 && substring->conv_type == 's')
	{
		if ((int)ft_strlen(s) > substring->precision)
			s[substring->precision] = '\0';
		if (substring->precision)
			save_parameter(substring, s);
		else
		{
			ft_strdel(&s);
			save_parameter(substring, "");
		}
	}
	else
		save_parameter(substring, s);
	return ;
}

void			adjust_string(t_substring *substring)
{
	set_string_parameter(substring);
	set_sign(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
}

void			adjust_percent_char(t_substring *substring)
{
	set_string_parameter(substring);
	set_sign(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
}

char			*conv_string(va_list *ap, t_substring *substring, int *attrs)
{
	(*attrs)++;
	substring->par_value = ft_strdup((char *)va_arg(*ap, void *));
	if (!(char *)substring->par_value)
		substring->par_value = ft_strdup("(null)");
	return (NULL);
}

char			*conv_percent_char(va_list *ap, t_substring *substring,
																	int *attrs)
{
	(void)ap;
	(void)attrs;
	substring->par_value = ft_strdup("%");
	return (NULL);
}

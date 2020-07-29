/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:33:06 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/09 18:12:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			set_char_parameter(t_substring *substring)
{
	char			*s;

	s = (char *)substring->par_value;
	save_parameter(substring, s);
	substring->o_string.parameter.content_size = 1;
	return ;
}

void				adjust_character(t_substring *substring)
{
	set_char_parameter(substring);
	set_sign(substring);
	set_zero_filler(substring);
	set_pre_filler(substring);
	set_post_filler(substring);
	return ;
}

char				*conv_character(va_list *ap, t_substring *substring,
															int *attrs)
{
	(*attrs)++;
	substring->par_value = ft_strnew(1);
	((char *)(substring->par_value))[0] = (char)va_arg(*ap, int);
	if (!((char *)(substring->par_value))[0])
		substring->o_string.add_null = 1;
	return (NULL);
}

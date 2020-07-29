/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:55:34 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/10 08:57:18 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		create_output_string(va_list *ap, const char *format, int fd,
																	char *str)
{
	size_t			attrs;
	t_list			**substring_list;
	t_list			**converter_list;
	t_list			**formatter_list;
	t_list			**type_list;

	attrs = 0;
	formatter_list = create_formatters();
	converter_list = create_converters();
	type_list = create_param_type_list();
	substring_list = split_string((char *)format, converter_list);
	add_param_type(substring_list, type_list);
	add_width_and_prediction(substring_list);
	attrs = convert_substrings(substring_list, ap, converter_list,
														formatter_list);
	attrs = print_formatted_string(substring_list, fd, str);
	release_memory(substring_list, converter_list, formatter_list, type_list);
	return (attrs);
}

int				ft_printf(const char *format, ...)
{
	va_list			ap;
	int				attrs;

	va_start(ap, format);
	attrs = create_output_string(&ap, format, 1, NULL);
	va_end(ap);
	return (attrs);
}

int				ft_dprintf(int fd, const char *format, ...)
{
	va_list			ap;
	int				attrs;

	va_start(ap, format);
	attrs = create_output_string(&ap, format, fd, NULL);
	va_end(ap);
	return (attrs);
}

int				ft_sprintf(char *str, const char *format, ...)
{
	va_list			ap;
	int				attrs;

	va_start(ap, format);
	attrs = create_output_string(&ap, format, 0, str);
	va_end(ap);
	return (attrs);
}

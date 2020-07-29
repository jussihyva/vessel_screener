/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:12:58 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/09 20:03:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				add_converter(t_substring *substring,
										t_list **converter_list,
										t_list **formatter_list)
{
	char			character;
	char			*input_string;
	t_list			*elem;

	input_string = substring->input_string;
	character = input_string[ft_strlen(input_string) - 1];
	elem = *converter_list;
	while (elem)
	{
		if (character == ((t_converter *)(elem->content))->character)
		{
			substring->converter = (t_converter *)(elem->content);
			substring->conv_type = substring->converter->character;
			get_formatters(substring, formatter_list);
			break ;
		}
		elem = elem->next;
	}
}

static void				convert_substring(t_substring *substring, va_list *ap,
											int *attrs)
{
	if (!substring->converter || !substring->converter->function_ptr)
	{
		substring->o_string.parameter.content =
											ft_strdup(substring->input_string);
		substring->o_string.parameter.content_size =
							ft_strlen(substring->o_string.parameter.content);
		substring->o_string.parameter.next = NULL;
	}
	else
		substring->converter->function_ptr(ap, substring, attrs);
	return ;
}

int						convert_substrings(t_list **list, va_list *ap,
											t_list **converter_list,
											t_list **formatter_list)
{
	t_list			*elem;
	t_substring		*substring;
	int				attrs;

	attrs = 0;
	elem = *list;
	while (elem)
	{
		substring = (t_substring *)(elem->content);
		substring->converter = NULL;
		substring->flags = 0;
		if (substring->input_string[0] == '%')
			add_converter(substring, converter_list, formatter_list);
		convert_substring(substring, ap, &attrs);
		if (substring->converter)
			substring->converter->adjust_width_prediction_ptr(substring);
		elem = elem->next;
	}
	return (attrs);
}

static t_list			*new_conv(void *function, char character,
									void *adjust_width_prediction_ptr)
{
	t_converter		*converter;
	size_t			converter_size;
	t_list			*elem;
	int				valid_flags;

	valid_flags = 0;
	converter_size = sizeof(*converter);
	converter = (t_converter *)ft_memalloc(converter_size);
	converter->character = character;
	converter->valid_flags = valid_flags;
	converter->function_ptr = function;
	converter->adjust_width_prediction_ptr = adjust_width_prediction_ptr;
	elem = ft_lstnew(converter, converter_size);
	free(converter);
	converter = NULL;
	return (elem);
}

t_list					**create_converters(void)
{
	t_list			**conv_list;

	conv_list = (t_list **)ft_memalloc(sizeof(*conv_list));
	ft_lstadd_e(conv_list, new_conv((void *)conv_percent_char, '%',
													adjust_percent_char));
	ft_lstadd_e(conv_list, new_conv((void *)conv_character, 'c',
													adjust_character));
	ft_lstadd_e(conv_list, new_conv((void *)conv_string, 's', adjust_string));
	ft_lstadd_e(conv_list, new_conv((void *)conv_pointer, 'p', adjust_pointer));
	ft_lstadd_e(conv_list, new_conv((void *)conv_int, 'd', adjust_int));
	ft_lstadd_e(conv_list, new_conv((void *)conv_int, 'i', adjust_int));
	ft_lstadd_e(conv_list, new_conv((void *)conv_unsigned_octal, 'o',
													adjust_unsigned_octal));
	ft_lstadd_e(conv_list, new_conv((void *)conv_unsigned_int, 'u',
													adjust_unsigned_int));
	ft_lstadd_e(conv_list, new_conv((void *)conv_unsigned_hex, 'x',
													adjust_unsigned_hex));
	ft_lstadd_e(conv_list, new_conv((void *)conv_unsigned_hex, 'X',
													adjust_unsigned_hex));
	ft_lstadd_e(conv_list, new_conv((void *)conv_float, 'f', adjust_float));
	return (conv_list);
}

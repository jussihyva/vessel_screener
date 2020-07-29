/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:09:58 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/19 10:00:54 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		set_default_values(t_substring *substring)
{
	substring->filler = ' ';
	substring->precision = -1;
	substring->width = -1;
	substring->formatter_list =
					(t_list **)ft_memalloc(sizeof(*substring->formatter_list));
	return ;
}

static void		save_substring(t_list **list, char *start_ptr, char *end_ptr)
{
	char			*substring;
	t_list			*elem;
	t_substring		*substring_elem;
	size_t			substring_elem_size;

	if (!(*end_ptr))
	{
		if (*start_ptr == '%')
			return ;
		end_ptr = start_ptr + ft_strlen(start_ptr) - 1;
	}
	end_ptr++;
	substring = (char *)ft_strnew(end_ptr - start_ptr);
	substring = ft_strncpy(substring, start_ptr, end_ptr - start_ptr);
	substring_elem_size = sizeof(*substring_elem);
	substring_elem = (t_substring *)ft_memalloc(substring_elem_size);
	substring_elem->input_string = substring;
	set_default_values(substring_elem);
	substring_elem->end_ptr = substring + ft_strlen(substring) - 2;
	elem = ft_lstnew(substring_elem, substring_elem_size);
	free(substring_elem);
	substring_elem = NULL;
	ft_lstadd_e(list, elem);
	return ;
}

static char		*create_chars_string(t_list **converter_list)
{
	char			*chars_string;
	int				i;
	t_list			*elem;

	i = 0;
	elem = *converter_list;
	while (elem && ++i)
		elem = elem->next;
	chars_string = (char *)ft_strnew(sizeof(*chars_string) * i);
	i = 0;
	elem = *converter_list;
	while (elem)
	{
		chars_string[i++] = ((t_converter *)(elem->content))->character;
		elem = elem->next;
	}
	chars_string[i] = '\0';
	return (chars_string);
}

static char		*string_for_converter(char *start_ptr,
					char *chars_string)
{
	if (*start_ptr == '%')
	{
		start_ptr++;
		while (*start_ptr && !ft_strchr(chars_string, *start_ptr))
			start_ptr++;
	}
	else
	{
		start_ptr++;
		while (*start_ptr && *start_ptr != '%')
			start_ptr++;
		if (*start_ptr)
			start_ptr--;
	}
	return (start_ptr);
}

t_list			**split_string(char *input_string, t_list **converter_list)
{
	char			*start_ptr;
	char			*end_ptr;
	t_list			**substring_list;
	char			*chars_string;

	chars_string = create_chars_string(converter_list);
	substring_list = (t_list **)ft_memalloc(sizeof(*substring_list));
	start_ptr = input_string;
	while (start_ptr && *start_ptr)
	{
		end_ptr = string_for_converter(start_ptr, chars_string);
		save_substring(substring_list, start_ptr, end_ptr);
		if (*end_ptr)
			start_ptr = end_ptr + 1;
		else
			break ;
	}
	ft_strdel(&chars_string);
	return (substring_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_substring_common_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:11:00 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/24 06:45:23 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			save_parameter(t_substring *substring, char *s)
{
	substring->o_string.parameter.content = s;
	substring->o_string.parameter.content_size = ft_strlen(s);
	substring->o_string.parameter.next = NULL;
	return ;
}

static void		set_elem_values(t_substring *substring, size_t content_size,
																char *content)
{
	substring->o_string.prefix.content_size = content_size;
	substring->o_string.prefix.content = content;
	substring->o_string.prefix.next = NULL;
	return ;
}

void			set_prefix(t_substring *substring)
{
	t_list		elem;
	char		conv_type;

	elem = substring->o_string.parameter;
	conv_type = substring->conv_type;
	if (elem.content && substring->flags & hash &&
											((char *)(elem.content))[0] != '0')
	{
		if (conv_type == 'o')
			set_elem_values(substring, 1, ft_strdup("0"));
		else if (conv_type == 'x' && ((char *)(elem.content))[0] != '\0')
			set_elem_values(substring, 2, ft_strdup("0x"));
		else if (conv_type == 'X' && ((char *)(elem.content))[0] != '\0')
			set_elem_values(substring, 2, ft_strdup("0X"));
	}
	else if (conv_type == 'p')
		set_elem_values(substring, 2, ft_strdup("0x"));
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_prediction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:16:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/24 06:45:23 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		save_width_and_prediction(char **ptr,
												t_list *substring_elem)
{
	t_substring		*substring;

	substring = (t_substring *)substring_elem->content;
	if (**ptr == '.')
	{
		substring->precision = ft_atoi(*ptr + 1);
		(*ptr)--;
		while (**ptr && ft_isdigit(**ptr))
			(*ptr)--;
		substring->width = ft_atoi(*ptr + 1);
	}
	else
	{
		substring->precision = -1;
		substring->width = ft_atoi(*ptr + 1);
	}
	if (*(*ptr + 1) == '0')
		(*ptr)++;
	return ;
}

void			add_width_and_prediction(t_list **substring_list)
{
	t_list			*substring_elem;
	char			*ptr;
	t_substring		*substring;

	substring_elem = *substring_list;
	while (substring_elem)
	{
		substring = (t_substring *)substring_elem->content;
		if (substring->input_string[0] == '%')
		{
			ptr = substring->end_ptr;
			while (ptr > substring->input_string && *ptr && (ft_isdigit(*ptr)))
				ptr--;
			if (*ptr == '.' || ptr < substring->end_ptr)
				save_width_and_prediction(&ptr, substring_elem);
			substring->end_ptr = ptr;
		}
		substring_elem = substring_elem->next;
	}
	return ;
}

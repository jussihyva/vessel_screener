/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:43:33 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/19 12:51:44 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				set_param_type(t_list **type_list,
														t_substring *substring)
{
	t_list			*type_elem;
	char			*start_ptr;
	t_param_type	*param_type;

	substring->param_type = NULL;
	type_elem = *type_list;
	while (type_elem)
	{
		param_type = (t_param_type *)type_elem->content;
		if ((substring->end_ptr - substring->input_string) >=
															param_type->length)
		{
			start_ptr = substring->end_ptr - param_type->length + 1;
			if (ft_strnequ(param_type->type_string, start_ptr,
															param_type->length))
			{
				substring->param_type = param_type;
				if (substring->input_string < start_ptr)
					substring->end_ptr = start_ptr - 1;
				break ;
			}
		}
		type_elem = type_elem->next;
	}
	return ;
}

void					add_param_type(t_list **list, t_list **type_list)
{
	t_list			*elem;
	t_substring		*substring;

	elem = *list;
	while (elem)
	{
		substring = (t_substring *)elem->content;
		set_param_type(type_list, substring);
		elem = elem->next;
	}
}

static t_list			*new_type(t_type type, char *s, int length)
{
	t_list			*type_elem;
	t_param_type	param_type;

	param_type.type = type;
	param_type.type_string = s;
	param_type.length = length;
	type_elem = ft_lstnew(&param_type, sizeof(param_type));
	return (type_elem);
}

t_list					**create_param_type_list(void)
{
	t_list			**type_list;

	type_list = (t_list **)ft_memalloc(sizeof(*type_list));
	ft_lstadd(type_list, new_type(L, "L", 1));
	ft_lstadd(type_list, new_type(t, "t", 1));
	ft_lstadd(type_list, new_type(z, "z", 1));
	ft_lstadd(type_list, new_type(j, "j", 1));
	ft_lstadd(type_list, new_type(l, "l", 1));
	ft_lstadd(type_list, new_type(ll, "ll", 2));
	ft_lstadd(type_list, new_type(h, "h", 1));
	ft_lstadd(type_list, new_type(hh, "hh", 2));
	return (type_list);
}

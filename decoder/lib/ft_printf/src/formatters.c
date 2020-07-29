/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:08:24 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/09 11:24:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			get_formatters(t_substring *substring, t_list **formatter_list)
{
	int				s_len;
	t_list			*elem;
	t_formatter		*formatter;

	elem = *formatter_list;
	while (elem)
	{
		formatter = (t_formatter *)elem->content;
		s_len = substring->end_ptr - substring->input_string + 1;
		while (s_len--)
		{
			if (substring->input_string[s_len] == formatter->character &&
				!(substring->flags & formatter->flag))
			{
				substring->flags |= formatter->flag;
				ft_lstadd_e(substring->formatter_list,
					ft_lstnew(elem->content, elem->content_size));
				break ;
			}
		}
		elem = elem->next;
	}
}

static t_list	*new_formatter(char character, t_flag flag)
{
	t_formatter		*formatter;
	size_t			formatter_size;
	t_list			*elem;

	formatter_size = sizeof(*formatter);
	formatter = (t_formatter *)ft_memalloc(formatter_size);
	formatter->character = character;
	formatter->flag = flag;
	elem = (t_list *)ft_memalloc(sizeof(*elem));
	elem->content = (void *)formatter;
	elem->content_size = formatter_size;
	elem->next = NULL;
	return (elem);
}

t_list			**create_formatters(void)
{
	t_list			**formatter_list;

	formatter_list = (t_list **)ft_memalloc(sizeof(*formatter_list));
	ft_lstadd_e(formatter_list, new_formatter('-', minus));
	ft_lstadd_e(formatter_list, new_formatter('+', plus));
	ft_lstadd_e(formatter_list, new_formatter(' ', space));
	ft_lstadd_e(formatter_list, new_formatter('0', zero));
	ft_lstadd_e(formatter_list, new_formatter('#', hash));
	return (formatter_list);
}

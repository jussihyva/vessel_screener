/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_memory_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 09:59:49 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/19 10:36:59 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		reset_elem(t_list elem)
{
	char	*s;

	s = (char *)elem.content;
	if (elem.content_size)
		ft_strdel(&s);
	return ;
}

static void		del_o_string(t_substring *elem)
{
	reset_elem(elem->o_string.pre_filler);
	reset_elem(elem->o_string.sign);
	reset_elem(elem->o_string.prefix);
	reset_elem(elem->o_string.zero_filler);
	reset_elem(elem->o_string.parameter);
	reset_elem(elem->o_string.post_filler);
}

void			del_substring(void *substring_elem, size_t size)
{
	t_substring		*elem;

	(void)size;
	elem = (t_substring *)substring_elem;
	ft_strdel(&elem->input_string);
	if (elem->formatter_list)
	{
		ft_lstdel(elem->formatter_list, *del_formatter);
		free(elem->formatter_list);
		elem->formatter_list = NULL;
		del_o_string(elem);
		elem->formatter_list = NULL;
	}
	free(substring_elem);
	substring_elem = NULL;
	return ;
}

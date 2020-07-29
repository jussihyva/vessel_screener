/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_substring_zero.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:21:18 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/11 09:23:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_zero_fillers(t_substring *substring)
{
	int		num_of_fillers;

	num_of_fillers = substring->precision -
								substring->o_string.parameter.content_size;
	if (ft_strchr("o", substring->conv_type))
		num_of_fillers -= substring->o_string.prefix.content_size;
	return (num_of_fillers);
}

static void		add_filler(t_list *elem, int num_of_fillers)
{
	char		*s;
	char		filler;

	filler = '0';
	if (num_of_fillers > 0)
	{
		s = ft_strnew(num_of_fillers);
		*(s + num_of_fillers) = '\0';
		elem->content_size = num_of_fillers;
		elem->content = s;
		while (num_of_fillers--)
			*(s + num_of_fillers) = filler;
	}
	return ;
}

void			set_zero_filler(t_substring *substring)
{
	int			num_fillers;

	if (ft_strchr("dixXpuof", substring->conv_type))
	{
		num_fillers = 0;
		if (substring->conv_type == 'f')
		{
			if (substring->width != -1 && !(substring->flags & minus) &&
				(substring->flags & zero))
				num_fillers = count_num_of_fillers(substring, substring->width);
			else if (substring->precision != -1)
				num_fillers = count_zero_fillers(substring);
		}
		else
		{
			if (substring->precision != -1)
				num_fillers = count_zero_fillers(substring);
			else if (substring->width != -1 && !(substring->flags & minus) &&
				(substring->flags & zero))
				num_fillers = count_num_of_fillers(substring, substring->width);
		}
		add_filler(&substring->o_string.zero_filler, num_fillers);
	}
	return ;
}

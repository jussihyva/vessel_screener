/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_memory_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 17:35:39 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/10 10:04:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			del_formatter(void *formatter, size_t size)
{
	(void)size;
	free(formatter);
	formatter = NULL;
	return ;
}

static void		del_converter(void *converter, size_t size)
{
	(void)size;
	free(converter);
	converter = NULL;
	return ;
}

static void		del_param_type(void *type, size_t size)
{
	(void)size;
	free(type);
	type = NULL;
	return ;
}

void			release_memory(t_list **substring_list, t_list **converter_list,
									t_list **formatter_list, t_list **type_list)
{
	ft_lstdel(substring_list, *del_substring);
	free(substring_list);
	substring_list = NULL;
	ft_lstdel(converter_list, *del_converter);
	free(converter_list);
	converter_list = NULL;
	ft_lstdel(formatter_list, *del_formatter);
	free(formatter_list);
	formatter_list = NULL;
	ft_lstdel(type_list, *del_param_type);
	free(type_list);
	type_list = NULL;
	return ;
}

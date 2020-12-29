/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:14:17 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/18 12:27:56 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"

void		release_string_array(char **str_array, size_t num_of_fields)
{
	if (str_array)
	{
		while(num_of_fields--)
			ft_memdel((void **)&str_array[num_of_fields]);
		ft_memdel((void **)str_array);
	}
	return ;
}

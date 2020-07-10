/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:14:17 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/10 11:45:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"

void		release_string_array(char **str_array)
{
	size_t		i;

	i = -1;
	while (str_array[++i])
		free(str_array[i]);
	free(str_array);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_123.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 13:19:02 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/12 14:10:49 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"
#include "message_123.h"

void	parse_message_123(char *ais_data, t_message *message)
{
	t_record_123	*record_123;

	record_123 = (t_record_123 *)ft_memalloc(sizeof(*record_123));
	ft_memcpy(record_123, ais_data, sizeof(*record_123));
	message->message_id = (int)record_123->message_id;
	message->mmsi = (size_t)record_123->mmsi3 << 22;
	message->mmsi += (size_t)record_123->mmsi2 << 14;
	message->mmsi += (size_t)record_123->mmsi1 << 6;
	message->mmsi += (size_t)record_123->mmsi0;
	message->speed_over_ground =
						(double)((size_t)record_123->speed_over_ground_1 << 4);
	message->speed_over_ground += (double)record_123->speed_over_ground_0;
	message->speed_over_ground /= 10;
	free(record_123);
	return ;
}

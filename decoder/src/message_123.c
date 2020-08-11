/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_123.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 13:19:02 by ubuntu            #+#    #+#             */
/*   Updated: 2020/08/02 22:04:54 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"
#include "message_123.h"

void	parse_message_123(char *ais_data, t_message_123 *message_123)
{
	t_record_123	*record_123;

	record_123 = (t_record_123 *)ft_memalloc(sizeof(*record_123));
	ft_memcpy(record_123, ais_data, sizeof(*record_123));
	message_123->message_id = (int)record_123->message_id;
	message_123->repeat_indicator = (int)record_123->repeat_indicator;
	message_123->mmsi = (size_t)record_123->mmsi3 << 22;
	message_123->mmsi += (size_t)record_123->mmsi2 << 14;
	message_123->mmsi += (size_t)record_123->mmsi1 << 6;
	message_123->mmsi += (size_t)record_123->mmsi0;
	message_123->navigational_status = (int)record_123->navigational_status_1 << 2;
	message_123->navigational_status += (int)record_123->navigational_status_0;
	message_123->rate_of_turn = (int)record_123->rate_of_turn_1 << 2;
	message_123->rate_of_turn += (int)record_123->rate_of_turn_0;
	message_123->speed_over_ground =
						(double)((size_t)record_123->speed_over_ground_1 << 4);
	message_123->speed_over_ground += (double)record_123->speed_over_ground_0;
	message_123->speed_over_ground /= 10;
	message_123->position_accuracy = (int)record_123->position_accuracy;
	message_123->longitude = (size_t)record_123->longitude_4 << 25;
	message_123->longitude += (size_t)record_123->longitude_3 << 17;
	message_123->longitude += (size_t)record_123->longitude_2 << 9;
	message_123->longitude += (size_t)record_123->longitude_1 << 1;
	message_123->longitude += (size_t)record_123->longitude_0;
	message_123->latitude = (size_t)record_123->latitude_3 << 21;
	message_123->latitude += (size_t)record_123->latitude_2 << 13;
	message_123->latitude += (size_t)record_123->latitude_1 << 5;
	message_123->latitude += (size_t)record_123->latitude_0;
	message_123->course_over_ground = (size_t)record_123->course_over_ground_2 << 9;
	message_123->course_over_ground += (size_t)record_123->course_over_ground_1 << 1;
	message_123->course_over_ground += (size_t)record_123->course_over_ground_0;
	message_123->true_heading = (size_t)record_123->true_heading_1 << 2;
	message_123->true_heading += (size_t)record_123->true_heading_0;
	message_123->timestamp.vessel = (int)record_123->timestamp;
	message_123->special_manoeuvre_indicator = (int)record_123->special_manoeuvre_indicator;
	message_123->spare = (int)record_123->spare;
	message_123->raim_flag = (int)record_123->raim_flag;
	message_123->communication_state = (size_t)record_123->communication_state_3 << 17;
	message_123->communication_state += (size_t)record_123->communication_state_2 << 9;
	message_123->communication_state += (size_t)record_123->communication_state_1 << 1;
	message_123->communication_state += (size_t)record_123->communication_state_0;
	message_123->dummy = (int)record_123->dummy;
	message_123->mid = message_123->mmsi;
	while (message_123->mid >= 1000)
		message_123->mid /= 10;
	free(record_123);
	return ;
}

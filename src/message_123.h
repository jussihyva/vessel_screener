/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_123.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 14:06:28 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/13 16:53:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_123_H
# define MESSAGE_123_H

typedef struct		s_record_123
{
	unsigned char		dummy_1					:	2,
						message_id				:	6;
	unsigned char		mmsi3;
	unsigned char		mmsi2;
	unsigned char		mmsi1;
	unsigned char		navigational_status_1	:	2,
						mmsi0					: 	6;
	unsigned char		rate_of_turn_1			:	6,
						navigational_status_0	:	2;
	unsigned char		speed_over_ground_1		:	6,
						rate_of_turn_0			:	2;
	unsigned char		longitude_4				:	3,
						position_accuracy		:	1,
						speed_over_ground_0		:	4;
	unsigned char		longitude_3				:	8;
	unsigned char		longitude_2				:	8;
	unsigned char		longitude_1				:	8;
	unsigned char		latitude_3				:	7,
						longitude_0				:	1;
	unsigned char		latitude_2				:	8;
	unsigned char		latitude_1				:	8;
	unsigned char		course_over_ground_2	:	3,
						latitude_0				:	5;
	unsigned char		course_over_ground_1	:	8;
	unsigned char		true_heading_1			:	7,
						course_over_ground_0	:	1;
	unsigned char		dummy_2					:	6,
						true_heading_0			:	2;
}					t_record_123;

#endif

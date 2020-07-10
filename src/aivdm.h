/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aivdm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:23:42 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/10 16:56:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AIVDM_H
# define AIVDM_H
# include "libft.h"
# include "ft_printf.h"
# include "errno.h"
# include <fcntl.h>

# define PRINT_OK 500
# define NUM_OF_FIELDS 7
# define MAX_NUM_OF_MESSAGE_TYPES 50
# define COUNTRIES 1000

typedef enum		e_flags
{
	e_file =  0b0001,
	e_leaks = 0b0010
}					t_flags;

typedef struct		s_opt
{
	short			flags;
	int				fd;
}					t_opt;

typedef enum		e_message_type
{
	e_1_position_report = 1,
	e_2_position_report = 2,
	e_3_position_report = 3
}					t_message_type;

typedef enum		e_error_code
{
	e_invalid_num_of_fields = 1,
	e_invalid_check_sum
}					t_error_code;

typedef struct		s_stream
{
	char			characters[4];
}					t_stream;

typedef struct		s_message_id
{
	unsigned char		dummy_1		:	2,
						message_id	:	6;
}					t_message_id;

typedef struct		s_message
{
	int				type_counter[MAX_NUM_OF_MESSAGE_TYPES];
	int				mmsi_mid_counter[COUNTRIES];
}					t_message;

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

void				ft_step_args(int *argc, char ***argv);
void				ft_read_opt(t_opt *opt, int *argc, char ***argv);
void				print_hex(char *file_content, ssize_t size);
void				print_bin(char *file_content, ssize_t size);
void				release_string_array(char **str_array);

#endif

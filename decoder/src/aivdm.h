/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aivdm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:23:42 by ubuntu            #+#    #+#             */
/*   Updated: 2020/08/02 22:50:59 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AIVDM_H
# define AIVDM_H
# include "libft.h"
# include "ft_printf.h"
# include "errno.h"
# include <fcntl.h>
#include <sqlite3.h>
#include <time.h>

# define PRINT_OK 500
# define NUM_OF_FIELDS 7
# define MAX_NUM_OF_MESSAGE_TYPES 50
# define COUNTRIES 1000

typedef enum		e_flags
{
	e_file = 0b0001,
	e_leaks = 0b0010
}					t_flags;

typedef struct		s_opt
{
	short			flags;
	int				fd;
}					t_opt;

typedef struct		s_timestamp
{
	int				vessel;
	time_t			ais_dispatcher;
	time_t			decoder;
}					t_timestamp;

typedef enum		e_message_type
{
	e_1_position_report = 1,
	e_2_position_report = 2,
	e_3_position_report = 3
}					t_message_type;

typedef enum		e_error_code
{
	e_invalid_num_of_fields = 1,
	e_unknown_message_type,
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

typedef struct		s_statistics
{
	int				type_counter[MAX_NUM_OF_MESSAGE_TYPES];
	int				mmsi_mid_counter[COUNTRIES];
}					t_statistics;

typedef struct		s_message_123
{
	t_timestamp		timestamp;
	int				message_id;
	int				repeat_indicator;
	int				mmsi;
	int				navigational_status;
	int				rate_of_turn;
	double			speed_over_ground;
	int				position_accuracy;
	int				longitude;
	int				latitude;
	int				course_over_ground;
	int				true_heading;
	int				special_manoeuvre_indicator;
	int				spare;
	int				raim_flag;
	int				communication_state;
	int				dummy;
}					t_message_123;

void				ft_step_args(int *argc, char ***argv);
void				ft_read_opt(t_opt *opt, int *argc, char ***argv);
int					validate_input_record(char **aivdm_record_array, char *line,
																size_t *ok_cnt);
void				print_hex(char *file_content, ssize_t size);
void				print_bin(char *file_content, ssize_t size);
void				release_string_array(char **str_array);
void				parse_message_123(char *ais_data, t_message_123 *message_123);
void				open_sqlite3(sqlite3 **db);
void				close_sqlite3(sqlite3 *db);
void				select_sqlite3(sqlite3 *db, int mmsi_mid);
char				**parse_input_line(char *line, int *ais_dispatcher_timestamp);

#endif

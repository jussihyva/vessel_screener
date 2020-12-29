/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aivdm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:23:42 by ubuntu            #+#    #+#             */
/*   Updated: 2020/08/06 13:24:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AIVDM_H
# define AIVDM_H
# include "libft.h"
# include "libjk.h"
# include "ft_printf.h"
# include <stdio.h>
# include <string.h>
# include <time.h>
# include "errno.h"
# include <fcntl.h>
# include <sqlite3.h>
# include <time.h>
# include <sys/time.h>

# define PRINT_OK 500
# define NUM_OF_FIELDS 7
# define MAX_NUM_OF_MESSAGE_TYPES 50
# define COUNTRIES 1000
# define PEM_CERT_FILE			"/home/user/.ssh/enclave_certificate.pem"
# define PEM_PRIVTE_KEY_FILE	"/home/user/.ssh/enclave_key.pem"
# define BUF_MAX_SIZE			8192
# define MESSAGE_BUF_SIZE		BUF_MAX_SIZE + 4096
# define USERNAME "matti"
# define PASSWORD "Simo"

typedef struct 						s_timeval
{
	__kernel_time_t			tv_sec;
	__kernel_suseconds_t	tv_usec;
}									t_timeval;

typedef enum					e_connection_status
{
	e_idle,
	e_waiting_msg0,
	e_waiting_msg1,
	e_waiting_msg2,
	e_waiting_msg3,
	e_waiting_msg4,
	e_send_msg0
}								t_connection_status;

typedef struct					s_influx_session
{
	void					*connection;
	t_connection_status		connection_status;
}								t_influx_session;

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
	int				mid;
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
													size_t number_of_fields);
void				print_hex(char *file_content, ssize_t size);
void				print_bin(char *file_content, ssize_t size);
void				release_string_array(char **str_array, size_t num_of_fields);
void				parse_message_123(char *ais_data, t_message_123 *message_123);
void				open_sqlite3(sqlite3 **db);
void				close_sqlite3(sqlite3 *db);
void				select_sqlite3(sqlite3 *db, int mmsi_mid);
char				**parse_input_line(char *line, t_message_123 *message_123);
void				print_message_123(char *line, t_message_123 *message_123);
void				insert_message_123(sqlite3 *db, char *line,
													t_message_123 *message_123);
t_influx_session	*setup_influxdb_connection(char *host_name, char *port_number);
void				write_influxdb(t_tls_connection *tls_connection,
													char *body, char *database);
void				store_message_123(t_influx_session *influx_session,
													t_message_123 *message_123);

#endif

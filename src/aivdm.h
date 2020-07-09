/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aivdm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:23:42 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/09 18:59:33 by jkauppi          ###   ########.fr       */
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

typedef struct		s_opt
{
	short	file	: 1,
			dummy	: 7;
	int		fd;
}					t_opt;

typedef enum		e_message_type
{
	e_1_position_report = 1
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
	int				*type_counter;
	int				*mmsi_mid_counter;
}					t_message;


typedef struct		s_record_123
{
	unsigned char		dummy_1		:	2,
						message_id	:	6;
	unsigned char		mmsi3;
	unsigned char		mmsi2;
	unsigned char		mmsi1;
	unsigned char		dummy_2		:	2,
						mmsi0		: 	6;
//	unsigned int		navigational_status	:	4;
//	unsigned int		dummy_3	:	6;
}					t_record_123;

void				ft_step_args(int *argc, char ***argv);
void				ft_read_opt(t_opt *opt, int *argc, char ***argv);
void				print_hex(char *file_content, ssize_t size);
void				print_bin(char *file_content, ssize_t size);

#endif

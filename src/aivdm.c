/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aivdm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:21:53 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/10 16:06:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"

static void		print_payload(t_record_123 *record_123, char *line, int mmsi)
{
	ft_printf("%s\n", line);
	ft_printf("Size of record 123: %d\n", sizeof(*record_123));
	print_bin((char *)record_123, sizeof(*record_123));
	ft_printf("MMSI: %-9d,  Message: %x\n", mmsi, record_123->message_id);
	return ;
}

static int		validate_record(char **aivdm_record_array, char *line,
																size_t *ok_cnt)
{
	t_error_code	error;
	size_t			number_of_fields;
	char			validate_char;

	(void)line;
	error = 0;
	number_of_fields = -1;
	while (aivdm_record_array[++number_of_fields])
		;
	if (number_of_fields != NUM_OF_FIELDS)
		error = e_invalid_num_of_fields;
	else
	{
		validate_char = aivdm_record_array[number_of_fields - 1][1];
		if (validate_char != '*')
			error = e_invalid_check_sum;
		else
		{
			(*ok_cnt)++;
			if (!(*ok_cnt % PRINT_OK))
				ft_printf("OK (%d)\n", *ok_cnt);
		}
	}
	if (error && *line)
		ft_printf("ERROR (%s)\n", line);
	return (error);
}

// static void		print_bits(size_t size, void *ptr)
// {
// 	unsigned char *data = (unsigned char *)ptr;
// 	unsigned char bit;
// 	int byte, shift;
// 	for (byte = size-1; byte >= 0; byte--)
// 	{
// 		for (shift = 7; shift >= 0; shift--)
// 		{
// 			bit = (data[byte] >> shift) & 1;
// 			ft_printf("%u", bit);
// 		}
// 	}
// 	ft_printf("\n");
// 	return ;
// }

static char		*ais_encoder(char *payload_string, int payload_string_length, char *crc_string)
{
	size_t		i;
	size_t		j;
	t_stream	*payload_data;
	size_t		payload_data_size;
	char		*ais_data;
	size_t		ais_data_size;
	int			padding;

	padding = crc_string[0] - '0';
	padding = padding;
	// if (padding)
	// {
	// 	ft_printf("Padding: %d String length: %d\n", padding, payload_string_length);
	// 	ft_printf("Payload: %s\n", payload_string);
	// }
	payload_data_size = payload_string_length / 4 + (payload_string_length % 4);
	payload_data = (t_stream *)ft_memalloc(sizeof(*payload_data) * payload_data_size);
	ft_memcpy(payload_data, payload_string, payload_string_length);
	ais_data_size = (sizeof(*payload_data)) * payload_data_size * 3 / 4;
	ais_data = (char *)ft_memalloc(sizeof(*ais_data) * ais_data_size);
	i = -1;
	while (++i < payload_data_size)
	{
		j = -1;
		while (++j < 4)
		{
			payload_data[i].characters[j] -= 48;
			if (payload_data[i].characters[j] > 40)
				payload_data[i].characters[j] -= 8;
		}
		ais_data[i * 3 + 0] = ((payload_data[i].characters[0] & 0x3f) << 2) +
								((payload_data[i].characters[1] & 0x30) >> 4);
		ais_data[i * 3 + 1] = ((payload_data[i].characters[1] & 0x0f) << 4)+
								((payload_data[i].characters[2] & 0x3c) >> 2);
		ais_data[i * 3 + 2] = ((payload_data[i].characters[2] & 0x03) << 6) +
								((payload_data[i].characters[3] & 0x3f) << 0);
	}
	free(payload_data);
	return (ais_data);
}

static void		count_messages(t_message *message, t_message_id *message_id)
{
	static int	counter = 0;
	int			message_type;
	int			i;
	int			max;
	int			max_id;

	message_type = (int)message_id->message_id;
	message->type_counter[message_type]++;
	counter++;
	if (!(counter % 20))
	{
		i = -1;
		while (++i < MAX_NUM_OF_MESSAGE_TYPES)
		{
			if (message->type_counter[i])
				ft_printf("%5d", i);
		}
		ft_printf("\n");
		max = 0;
		i = -1;
		while (++i < MAX_NUM_OF_MESSAGE_TYPES)
		{
			if (message->type_counter[i])
			{
				ft_printf("%5d", message->type_counter[i]);
				if (max <= message->type_counter[i])
				{
					max = message->type_counter[i];
					max_id = i;
				}
			}
		}
		ft_printf("\n");
		ft_printf("Most frequent message type: %d\n", max_id);
	}
	return ;
}

static void		count_mmsi_mid(t_message *message, int mmsi_mid)
{
	static int	counter = 0;
	int			i;
	int			max;
	int			max_id;

	if (mmsi_mid < 100)
	{
		ft_printf("Too small\n");
		return ;
	}
	message->mmsi_mid_counter[mmsi_mid]++;
	counter++;
	if (!(counter % 20))
	{
		i = -1;
		while (++i < COUNTRIES)
		{
			if (message->mmsi_mid_counter[i])
				ft_printf("%5d", i);
		}
		ft_printf("\n");
		max = 0;
		i = -1;
		while (++i < COUNTRIES)
		{
			if (message->mmsi_mid_counter[i])
			{
				ft_printf("%5d", message->mmsi_mid_counter[i]);
				if (max <= message->mmsi_mid_counter[i])
				{
					max = message->mmsi_mid_counter[i];
					max_id = i;
				}
			}
		}
		ft_printf("\n");
		ft_printf("Most frequent country: %d\n", max_id);
	}
	return ;
}

int				main(int argc, char **argv)
{
	char			*line;
	char			**aivdm_record_array;
	size_t			ok_cnt;
	t_message_id	*message_id;
	t_record_123	*record_123;
	char			*ais_data;
	int				mmsi;
	int				mmsi_mid;
	t_message		*message;
	t_opt			*opt;
	char			*payload_string;
	char			*payload_string_tmp;
	int				payload_string_length;
	char			*padding;
	double			sog;

	ft_step_args(&argc, &argv);
	opt = (t_opt *)ft_memalloc(sizeof(*opt));
	ft_read_opt(opt, &argc, &argv);
	line = NULL;
	ok_cnt = 0;
	message = (t_message *)ft_memalloc(sizeof(*message));
	message_id = (t_message_id *)ft_memalloc(sizeof(*message_id));
	while (ft_get_next_line(opt->fd, &line))
	{
//		ft_printf("%s\n", line);
		aivdm_record_array = (char **)ft_strsplit(line, ',');
		if (!validate_record(aivdm_record_array, line, &ok_cnt))
		{
			if (*aivdm_record_array[2] == '1')
			{
				payload_string = ft_strdup(aivdm_record_array[5]);
//				ft_printf("%s\n", line);
			}
			else
			{
				payload_string_tmp = payload_string;
				payload_string = ft_strjoin(payload_string_tmp, aivdm_record_array[5]);
				ft_strdel(&payload_string_tmp);
			}
			if (*aivdm_record_array[2] == *aivdm_record_array[1])
			{
				payload_string_length = ft_strlen(payload_string);
				padding = aivdm_record_array[6];
				ais_data = ais_encoder(payload_string, payload_string_length, padding);
				ft_memcpy(message_id, ais_data, sizeof(*message_id));
				count_messages(message, message_id);
				if ((int)message_id->message_id > 0  &&
														(int)message_id->message_id < 8)
				{
					if ((t_message_type)message_id->message_id == e_1_position_report)
					{
						record_123 = (t_record_123 *)ft_memalloc(sizeof(*record_123));
						ft_memcpy(record_123, ais_data, sizeof(*record_123));
						mmsi = (size_t)record_123->mmsi3 << 22;
						mmsi += (size_t)record_123->mmsi2 << 14 ;
						mmsi += (size_t)record_123->mmsi1 << 6;
						mmsi += (size_t)record_123->mmsi0;
						sog = (double)((size_t)record_123->speed_over_ground_1 << 4);
						sog += (double)record_123->speed_over_ground_0;
						sog /= 10;
						ft_printf("SOG: %.1f\n", sog);
						if (sog)
							ft_printf("%s\n", line);
						mmsi_mid = mmsi;
						if (mmsi_mid < 1000)
							print_payload(record_123, line, mmsi);
						while (mmsi_mid >= 1000)
							mmsi_mid /= 10;
						count_mmsi_mid(message, mmsi_mid);
						free(record_123);
					}
				}
				ft_strdel(&payload_string);
				free(ais_data);
			}
		}
		ft_strdel(&line);
		release_string_array(aivdm_record_array);
	}
	ft_strdel(&payload_string);
	ft_strdel(&line);
	free(message);
	free(opt);
	free(message_id);
	if (opt->flags & e_leaks)
		system("leaks aivdm");
	return (0);
}

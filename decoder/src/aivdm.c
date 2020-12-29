/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aivdm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:21:53 by ubuntu            #+#    #+#             */
/*   Updated: 2020/08/06 13:13:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"

void		print_message_123(char *line, t_message_123 *message_123)
{
    struct tm	ts;
    char		buf[80];

    ts = *localtime(&message_123->timestamp.ais_dispatcher);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
	ft_printf("%s\n", line);
	ft_printf("AIS time: %d %s (%d)\n", message_123->timestamp.ais_dispatcher, buf, message_123->timestamp.vessel);
	ft_printf("%s %s %10s %s %s %s %s %s %s %s %s %s %s %s %s %s %s ",
		"message_id", "repeat_indicator", "mmsi", "navigational_status",
		"rate_of_turn", "speed_over_ground", "position_accuracy", "longitude",
		"latitude", "course_over_ground", "true_heading", "timestamp",
		"special_manoeuvre_indicator", "spare", "raim_flag",
		"communication_state", "dummy\n");
//	ft_printf("MMSI: %-9d,  Message: %x\n", message_123->mmsi, message_123->message_id);
	ft_printf(" %8d", message_123->message_id);
	ft_printf(" %16d", message_123->repeat_indicator);
	ft_printf(" %10d", message_123->mmsi);
	ft_printf(" %19d", message_123->navigational_status);
	ft_printf(" %12d", message_123->rate_of_turn);
	ft_printf(" %17f", message_123->speed_over_ground);
	ft_printf(" %17d", message_123->position_accuracy);
	ft_printf(" %9d", message_123->longitude);
	ft_printf(" %8d", message_123->latitude);
	ft_printf(" %18d", message_123->course_over_ground);
	ft_printf(" %12d", message_123->true_heading);
	ft_printf(" %9d", message_123->timestamp.vessel);
	ft_printf(" %27d", message_123->special_manoeuvre_indicator);
	ft_printf(" %5d", message_123->spare);
	ft_printf(" %9d", message_123->raim_flag);
	ft_printf(" %19d", message_123->communication_state);
	ft_printf(" %5d\n", message_123->dummy);
	return ;
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
	// int			padding;

	// padding = crc_string[0] - '0';
	// padding = padding;
	// if (padding)
	// {
	// 	ft_printf("Padding: %d String length: %d\n", padding, payload_string_length);
	// 	ft_printf("Payload: %s\n", payload_string);
	// }
	(void)crc_string;
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

static void		count_messages(t_statistics *statistics,
													t_message_id *message_id)
{
	static int	counter = 0;
	int			message_type;
	int			i;
	int			max;
	int			max_id;

	message_type = (int)message_id->message_id;
	statistics->type_counter[message_type]++;
	counter++;
	if (!(counter % 20))
	{
		i = -1;
		while (++i < MAX_NUM_OF_MESSAGE_TYPES)
		{
			if (statistics->type_counter[i])
				ft_printf("%5d", i);
		}
		ft_printf("\n");
		max = 0;
		i = -1;
		while (++i < MAX_NUM_OF_MESSAGE_TYPES)
		{
			if (statistics->type_counter[i])
			{
				ft_printf("%5d", statistics->type_counter[i]);
				if (max <= statistics->type_counter[i])
				{
					max = statistics->type_counter[i];
					max_id = i;
				}
			}
		}
		ft_printf("\n");
		ft_printf("Most frequent message type: %d\n", max_id);
	}
	return ;
}

static void		count_mmsi_mid(t_statistics *statistics, int mmsi, sqlite3 *db,
														int payload_max_length)
{
	static int		counter = 0;
	int				i;
	int				max;
	int				max_id;
	int				mmsi_mid;

	mmsi_mid = mmsi;
	while (mmsi_mid >= 1000)
		mmsi_mid /= 10;
	if (mmsi_mid != 230)
		ft_printf("%d\n", mmsi);
	select_sqlite3(db, mmsi_mid);
	statistics->mmsi_mid_counter[mmsi_mid]++;
	counter++;
	if (!(counter % 200))
	{
		i = -1;
		while (++i < COUNTRIES)
		{
			if (statistics->mmsi_mid_counter[i])
				ft_printf("%5d", i);
		}
		ft_printf("\n");
		max = 0;
		i = -1;
		while (++i < COUNTRIES)
		{
			if (statistics->mmsi_mid_counter[i])
			{
				ft_printf("%5d", statistics->mmsi_mid_counter[i]);
				if (max <= statistics->mmsi_mid_counter[i])
				{
					max = statistics->mmsi_mid_counter[i];
					max_id = i;
				}
			}
		}
		ft_printf("\n");
		ft_printf("Most frequent country: %d\n", max_id);
		ft_dprintf(2, "Maximum length of a payload string: %d\n", payload_max_length);
	}
	return ;
}

int				main(int argc, char **argv)
{
	char				*line;
	char				**aivdm_record_array;
	size_t				ok_cnt;
	t_message_id		*message_id;
	char				*ais_data;
	t_statistics		*statistics;
	t_opt				*opt;
	char				*payload_string;
	char				*payload_string_tmp;
	int					payload_string_length;
	char				*padding;
	t_message_123		*message_123;
	sqlite3				*db;
	int					payload_max_length;
	int					ais_dispatcher_timestamp;
	t_influx_session	*influx_session;

	ft_step_args(&argc, &argv);
	influx_session = setup_influxdb_connection("52.23.5.140", "8086");
	open_sqlite3(&db);
	opt = (t_opt *)ft_memalloc(sizeof(*opt));
	ft_read_opt(opt, &argc, &argv);
	line = NULL;
	ok_cnt = 0;
	message_123 = (t_message_123 *)ft_memalloc(sizeof(*message_123));
	statistics = (t_statistics *)ft_memalloc(sizeof(*statistics));
	message_id = (t_message_id *)ft_memalloc(sizeof(*message_id));
	payload_string = NULL;
	payload_max_length = 0;
	while (ft_get_next_line(opt->fd, &line))
	{
		ais_dispatcher_timestamp = 0;
		aivdm_record_array = parse_input_line(line, message_123);
		if (ais_dispatcher_timestamp)
			message_123->timestamp.ais_dispatcher = ais_dispatcher_timestamp;
		if(aivdm_record_array)
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
				if (payload_string_length > payload_max_length)
				{
					ft_printf("Length of a payload string: %d\n", payload_string_length);
					payload_max_length = payload_string_length;
				}
				padding = aivdm_record_array[6];
				ais_data = ais_encoder(payload_string, payload_string_length, padding);
				ft_memcpy(message_id, ais_data, sizeof(*message_id));
				count_messages(statistics, message_id);
				if ((int)message_id->message_id > 0  &&
														(int)message_id->message_id < 8)
				{
					if ((t_message_type)message_id->message_id >= e_1_position_report &&
							(t_message_type)message_id->message_id <= e_3_position_report)
					{
						parse_message_123(ais_data, message_123);
						store_message_123(influx_session, message_123);
						if (message_123->speed_over_ground >= 0)
						{
							insert_message_123(db, line, message_123);
						}
						count_mmsi_mid(statistics, message_123->mmsi, db, payload_max_length);
						usleep(500 * 1000);
					}
				}
				ft_strdel(&payload_string);
				free(ais_data);
			}
			release_string_array(aivdm_record_array, NUM_OF_FIELDS);
		}
		ft_strdel(&line);
	}
	close_sqlite3(db);
	ft_strdel(&payload_string);
	ft_strdel(&line);
	free(statistics);
	free(opt);
	free(message_id);
	if (opt->flags & e_leaks)
		system("leaks aivdm");
	return (0);
}

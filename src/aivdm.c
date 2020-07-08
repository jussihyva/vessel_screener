/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aivdm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:21:53 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/08 19:32:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"

static void		print_payload(char *payload)
{
	(void)payload;
	return ;
}

static int		validate_record(char validate_char, char *line, size_t *ok_cnt,
														size_t number_of_fields)
{
	t_error_code	error;

	error = 0;
	if (validate_char != '*' || number_of_fields != NUM_OF_FIELDS)
	{
		if (number_of_fields != NUM_OF_FIELDS)
			error = e_invalid_num_of_fields;
		else
			error = e_invalid_check_sum;
		ft_printf("ERROR (%s)\n", line);
		return (error);
	}
	else
	{
		(*ok_cnt)++;
		if (!(*ok_cnt % PRINT_OK))
			ft_printf("OK (%d)\n", *ok_cnt);
		return (error);
	}
}

static size_t	print_record(char **aivdm_record_array)
{
	size_t		i;
	int			is_first;
//	int			length;

	is_first = 1;
	i = -1;
	while (aivdm_record_array[++i])
	{
		if(!is_first)
			is_first = 0;
		// else
		// 	ft_printf("\t");
		// if (i == 5)
		// 	ft_printf("???");
		// else if (i == 6)
		// {
		// 	length = ft_strlen(aivdm_record_array[i]);
		// 	aivdm_record_array[i][length - 1] = '\0';
		// 	ft_printf("%s", aivdm_record_array[i]);
		// }
		// else
		// 	ft_printf("%s", aivdm_record_array[i]);
	}
//	ft_printf("\n");
	return (i);
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

static char		*ais_encoder(t_stream *payload_data, size_t payload_data_size)
{
	size_t		i;
	char		*ais_data;
	size_t		ais_data_size;

	ais_data_size = sizeof(*payload_data) * payload_data_size * 4 / 3;
	ais_data = (char *)ft_memalloc(sizeof(*ais_data) * ais_data_size);
	i = -1;
	while (++i < payload_data_size)
	{
		payload_data[i].char_1 -= 48;
		payload_data[i].char_2 -= 48;
		payload_data[i].char_3 -= 48;
		payload_data[i].char_4 -= 48;
		if (payload_data[i].char_1 > 40)
			payload_data[i].char_1 -= 8;
		if (payload_data[i].char_2 > 40)
			payload_data[i].char_2 -= 8;
		if (payload_data[i].char_3 > 40)
			payload_data[i].char_3 -= 8;
		if (payload_data[i].char_4 > 40)
			payload_data[i].char_4 -= 8;
		ais_data[i * 3 + 0] = ((payload_data[i].char_1 & 0x3f) << 2) + ((payload_data[i].char_2 & 0x30) >> 4);
		ais_data[i * 3 + 1] = ((payload_data[i].char_2 & 0x0f) << 4)+ ((payload_data[i].char_3 & 0x3c) >> 2);
		ais_data[i * 3 + 2] = ((payload_data[i].char_3 & 0x03) << 6) + ((payload_data[i].char_4 & 0x3f) << 0);
	}
//	print_hex(ais_data, 6);
//	print_bin(ais_data, 18);
	return (ais_data);
}

// static void		create_ais_converter_table(void)
// {
// 	char		*ais_conv_table;

// 	ais_conv_table = (char *)ft_memalloc(sizeof(*ais_conv_table) * 256);
// 	ais_conv_table['0'] = 1;
// 	return ;
// }

int				main()
{
	char			*line;
	char			**aivdm_record_array;
	t_stream		*payload_data;
	size_t			payload_data_size;
	size_t			number_of_fields;
	size_t			ok_cnt;
	t_message_id	*message_id;
	t_record_123	*record_123;
	char			*ais_data;
	int				mmsi;

	line = NULL;
	ok_cnt = 0;
	message_id = (t_message_id *)ft_memalloc(sizeof(*message_id));
	while (1)
	{
		ft_get_next_line(0, &line);
		if (!(*line))
			break ;
		aivdm_record_array = (char **)ft_strsplit(line, ',');
		number_of_fields = print_record(aivdm_record_array);
		if (validate_record(aivdm_record_array[number_of_fields - 1][1], line,
													&ok_cnt, number_of_fields))
			break ;
		payload_data_size = ft_strlen(aivdm_record_array[5]) / 4;
		payload_data = (t_stream *)ft_memalloc(sizeof(*payload_data) * payload_data_size);
		ft_memcpy(payload_data, aivdm_record_array[5], ft_strlen(aivdm_record_array[5]));
		ais_data = ais_encoder(payload_data, payload_data_size);
		ft_memcpy(message_id, ais_data, sizeof(*message_id));
		if ((int)message_id->message_id > 0  && (int)message_id->message_id < 8)
		{
			record_123 = (t_record_123 *)ft_memalloc(sizeof(*record_123));
			ft_memcpy(record_123, ais_data, sizeof(*record_123));
			print_payload(aivdm_record_array[0]);
			mmsi = (int)record_123->mmsi3 << 22;
			mmsi += (int)record_123->mmsi2 << 14 ;
			mmsi += (int)record_123->mmsi1 << 6;
			mmsi += (int)record_123->mmsi0;
			ft_printf("MMSI: %-9d,  Message: %x\n", mmsi, record_123->message_id);
		}
		// else
		// 	ft_printf("%d\n", message_id->message_id);
		ft_strdel(&line);
	}
	return (0);

}

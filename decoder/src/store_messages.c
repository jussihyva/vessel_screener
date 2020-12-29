#include "aivdm.h"

void	store_message_123(t_influx_session *influx_session,
													t_message_123 *message_123)
{
	char		*influx_query_string;
	char		*error_message;
	int			time_stamp;

	(void)influx_session;
	error_message = NULL;
	if (message_123->message_id >= 1 && message_123->message_id <= 3)
	{
		if(message_123->timestamp.ais_dispatcher == 0)
			time_stamp = message_123->timestamp.decoder;
		else
			time_stamp = message_123->timestamp.ais_dispatcher;
		influx_query_string = (char *)ft_memalloc(sizeof(*influx_query_string) *
																		100000);
		ft_sprintf(influx_query_string, "vessel_ais,mmsi=%d,message_id=%d decoder_time=%di,ais_dispatcher_time=%di,repeat_indicator=%di,mmsi=%di,mid=%di,navigational_status=%di,rate_of_turn=%di,speed_over_ground=%.2f,position_accuracy=%di,longitude=%.5f,latitude=%.5f,course_over_ground=%di,true_heading=%di,timestamp=%di,special_manoeuvre_indicator=%di,spare=%di,raim_flag=%di,communication_state=%di,dummy=%di %d\n",
			message_123->mmsi, message_123->message_id,
			(int)message_123->timestamp.decoder, (int)message_123->timestamp.ais_dispatcher, 
			message_123->repeat_indicator, message_123->mmsi, message_123->mid,
			message_123->navigational_status, message_123->rate_of_turn,
			message_123->speed_over_ground, message_123->position_accuracy,
			(double)message_123->longitude, (double)message_123->latitude,
			message_123->course_over_ground, message_123->true_heading,
			message_123->timestamp.vessel, message_123->special_manoeuvre_indicator,
			message_123->spare, message_123->raim_flag,
			message_123->communication_state, message_123->dummy,
			time_stamp);
		write_influxdb(influx_session->connection, influx_query_string, "Test_01");
		ft_printf("%s\n", influx_query_string);
		ft_strdel(&influx_query_string);
	}
	return ;
}

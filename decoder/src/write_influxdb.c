#include "aivdm.h"


void	write_influxdb(t_tls_connection *tls_connection, char *body,
																char *database)
{
	char		header[BUF_MAX_SIZE];
	char		read_buf[BUF_MAX_SIZE];
	int			chars;
	int			start;
	int			end;

	sprintf(header,
		"POST /write?db=%s&u=%s&p=%s&precision=s HTTP/1.1\r\nHost: none\r\nContent-Length: %ld\r\n\r\n",
									database, USERNAME, PASSWORD, strlen(body));
	SSL_write(tls_connection->ssl_bio, header, strlen(header));
	SSL_write(tls_connection->ssl_bio, body, strlen(body));
	start = clock();
	end = start + CLOCKS_PER_SEC;
	while((chars = SSL_read(tls_connection->ssl_bio, read_buf, BUF_MAX_SIZE)) == -1 &&
				end > clock())
		;
	if(chars > 0)
		ft_printf("%s", read_buf);
	while((chars = SSL_read(tls_connection->ssl_bio, read_buf, BUF_MAX_SIZE)) > 0)
		ft_printf("%s", read_buf);
	return ;
}

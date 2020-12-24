#include "libjk.h"

t_tls_connection	*jk_setup_tls_connection(char *hostname, char *port,
													int socket_fd, SSL_CTX *ctx)
{
	int					error;
    struct sockaddr_in	addr;
	t_tls_connection	*tls_connection;

	tls_connection = (t_tls_connection *)ft_memalloc(sizeof(*tls_connection));
	tls_connection->socket_fd = socket_fd;
	error = -1;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port));
	addr.sin_addr.s_addr = inet_addr(hostname);
	if ((error = connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr))) != -1)
	{
		tls_connection->ssl_bio = SSL_new(ctx);
		SSL_set_fd(tls_connection->ssl_bio, tls_connection->socket_fd);
		if((error = SSL_connect(tls_connection->ssl_bio)) == -1)
		{
			printf("SSL connect error\n");
			SSL_free(tls_connection->ssl_bio);
			tls_connection->ssl_bio = NULL;
			tls_connection = NULL;
		}
	}
	else
		tls_connection = NULL;
	return(tls_connection);
}


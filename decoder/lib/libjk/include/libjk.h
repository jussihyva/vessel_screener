#ifndef LIBE_H
# define LIBE_H
# include "libft.h"
# include <openssl/ssl.h>
# include <openssl/err.h>
# include <netinet/in.h>
# include <unistd.h>
# include <sys/socket.h>
# include <arpa/inet.h>

typedef struct	s_tls_connection
{
	int						socket_fd;
	SSL_CTX					*ctx;
	SSL						*ssl_bio;
}				t_tls_connection;

SSL_CTX			*jk_create_ctx(const SSL_METHOD *tls_method,
							char *pem_cert_file, char *pem_private_key_file);

#endif

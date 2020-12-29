#include "libjk.h"

SSL_CTX			*jk_start_tls_client(char *pem_cert_file,
									char *pem_private_key_file, int *socket_fd)
{
	SSL_CTX				*ctx;
	const SSL_METHOD	*tls_method;

	if((*socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != -1)
	{
		tls_method = TLS_client_method();
		ctx = jk_create_ctx(tls_method, pem_cert_file, pem_private_key_file);
		if(!ctx)
			close(*socket_fd);
	}
	else
		ctx = NULL;
	return(ctx);
}

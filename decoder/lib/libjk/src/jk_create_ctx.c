#include "libjk.h"

SSL_CTX		*jk_create_ctx(const SSL_METHOD	*tls_method, char *pem_cert_file,
													char *pem_private_key_file)
{
	SSL_CTX				*ctx;
	int					error;

	ctx = SSL_CTX_new(tls_method);
	error = 0;
	if(!SSL_CTX_use_certificate_file(ctx, pem_cert_file, SSL_FILETYPE_PEM))
		error = 1;
	else if(!SSL_CTX_use_PrivateKey_file(ctx, pem_private_key_file,
															SSL_FILETYPE_PEM))
		error = 1;
	else if(!SSL_CTX_check_private_key(ctx))
		error = 1;
	if(error)
	{
		fprintf(stderr, "Error setting up SSL_CTX\n");
		ERR_print_errors_fp(stderr);
		SSL_CTX_free(ctx);
		ctx = NULL;
	}
	return(ctx);
}

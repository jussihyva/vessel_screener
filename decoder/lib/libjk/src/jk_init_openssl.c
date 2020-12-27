#include "libjk.h"

void		jk_init_openssl(void)
{
	SSL_load_error_strings();
	ERR_load_crypto_strings();
	SSL_library_init();
	OpenSSL_add_ssl_algorithms();
	OpenSSL_add_all_ciphers();
}


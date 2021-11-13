#if !defined(EH_UPLOADER_REQBUILDER_H)
#define EH_UPLOADER_REQBUILDER_H

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include <curl/curl.h>

#include "../config/config.h"

void add_file(curl_mime *mime, const char *file_path);
void add_domains(curl_mime *mime, eh_config_t *config);
void add_user_data(curl_mime *mime, eh_config_t *config, const char *encryption_key);

#endif // EH_UPLOADER_REQBUILDER_H

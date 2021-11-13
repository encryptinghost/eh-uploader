#include "reqbuilder.h"

void add_file(curl_mime *mime, const char *file_path) {
    curl_mimepart *part = curl_mime_addpart(mime);

    curl_mime_name(part, "file");
    curl_mime_filename(part, file_path);
    curl_mime_filedata(part, file_path);
}

void add_domains(curl_mime *mime, eh_config_t *config) {
    char *str = (char *) malloc(1024);
    int curr_size = 1024;
    int curr_i = 1;

    str[0] = '[';

    for (int i = 0; i < config->domains_len; i++) {
        int curr_len = strlen(config->domains[i]);
        
        if (curr_size - curr_i - curr_len - 3 < 0) {
            str = (char *) realloc(str, curr_size + 1024);
            curr_size += 1024;
        }

        if (i > 0) {
            str[curr_i++] = ',';
        }

        str[curr_i++] = '"';

        strcpy(str + curr_i, config->domains[i]);
        curr_i += curr_len;

        str[curr_i++] = '"';
    }

    str[curr_i++] = ']';
    str[curr_i] = 0;

    curl_mimepart *part = curl_mime_addpart(mime);

    curl_mime_name(part, "domains");
    curl_mime_data(part, str, CURL_ZERO_TERMINATED);
}

void add_user_data(curl_mime *mime, eh_config_t *config, const char *encryption_key) {
    curl_mimepart *part = curl_mime_addpart(mime);

    curl_mime_name(part, "password");
    curl_mime_data(part, encryption_key, CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);

    curl_mime_name(part, "userKey");
    curl_mime_data(part, config->user_key, CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);

    curl_mime_name(part, "urlStyle");
    curl_mime_data(part, url_style_as_string(config->url_style), CURL_ZERO_TERMINATED);
}
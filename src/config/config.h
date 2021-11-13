#if !defined(EH_UPLOADER_CONFIG_H)
#define EH_UPLOADER_CONFIG_H

#include <stdio.h>
#include <stddef.h>

#include "../defs/url_style.h"
#include "../defs/errors.h"
#include "../util/util.h"

struct eh_config_s {
    char *user_key;
    
    eh_url_style_t url_style;

    char **domains;
    size_t domains_len;
};

typedef struct eh_config_s eh_config_t;

eh_error_t read_config(const char *path, eh_config_t *config);
const char *url_style_as_string(eh_url_style_t url_style);

#endif // EH_UPLOADER_CONFIG_H

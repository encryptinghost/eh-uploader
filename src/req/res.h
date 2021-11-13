#if !defined(EH_UPLOADER_RES_H)
#define EH_UPLOADER_RES_H

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct eh_res_s {
    int success;
    char *url;
    char *deletion_url;
};

typedef struct eh_res_s eh_res_t;

struct eh_res_cbdata_s {
    size_t current_size;
    char *data;
};

typedef struct eh_res_cbdata_s eh_res_cbdata_t;

size_t eh_res_callback(char *ptr, size_t size, size_t nmemb, eh_res_cbdata_t *data);

#endif // EH_UPLOADER_RES_H

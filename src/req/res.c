#include "res.h"

#include <stdio.h>

size_t eh_res_callback(char *ptr, size_t size, size_t nmemb, eh_res_cbdata_t *data) {
    size_t old_size = data->current_size;
    
    data->current_size = old_size + nmemb;

    data->data = (char *) realloc(data->data, data->current_size);
    memcpy(data->data + old_size, ptr, nmemb);

    return nmemb;
}
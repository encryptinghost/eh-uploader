#if !defined(EH_UPLOADER_REQ_H)
#define EH_UPLOADER_REQ_H

#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "../config/config.h"
#include "../util/util.h"

#include "reqbuilder.h"
#include "res.h"

struct eh_req_s {
    eh_config_t *config;
    char *file_path;
    char *encryption_key;
};

typedef struct eh_req_s eh_req_t;

void eh_upload_file(eh_req_t *req, eh_res_t *res);

#endif // EH_UPLOADER_REQ_H

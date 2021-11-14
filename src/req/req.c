#include "req.h"

#define MAX_TOKENS 32

#include <stdio.h>

static int extract_urls(eh_res_t *res, eh_res_cbdata_t *data) {
    jsmn_parser parser;
    jsmn_init(&parser);

    jsmntok_t tokens[MAX_TOKENS];

    int token_count = jsmn_parse(&parser, data->data, data->current_size, tokens, MAX_TOKENS);

    if (token_count != 8 || tokens[0].type != JSMN_OBJECT) return 1;
    
    jsmntok_t *data_token = &tokens[1];
    if (jsoneq(data->data, data_token, "data") == 1) return 1;

    jsmntok_t *data_value = &tokens[2];
    if (data_value->type != JSMN_ARRAY || data_value->size != 1) return 1;

    // Actual data object begins at token index 4. Fuck ShareX for the shit example and Ralf, just because.
    // index | what
    //   4   | the key "Url"
    //   5   | the value of "Url"
    //   6   | the key "DeletionUrl"
    //   7   | the value of "DeletionUrl"

    if (jsoneq(data->data, &tokens[4], "Url") == 1 || tokens[5].type != JSMN_STRING) return 1;
    if (jsoneq(data->data, &tokens[6], "DeletionUrl") == 1 || tokens[7].type != JSMN_STRING) return 1;

    res->url = json_strcpy(data->data, &tokens[5]);
    res->deletion_url = json_strcpy(data->data, &tokens[7]);

    return 0;
}

void eh_upload_file(eh_req_t *req, eh_res_t *res) {
    memset(res, 0, sizeof(eh_res_t));

    CURL *curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "Couldn't initialize libcurl.\n");
        return;
    }

    curl_mime *mime = curl_mime_init(curl);

    add_file(mime, req->file_path);
    add_user_data(mime, req->config, req->encryption_key);
    add_domains(mime, req->config);

    eh_res_cbdata_t cbdata;

    cbdata.current_size = 0;
    cbdata.data = (char *) malloc(1); // We can consistently use realloc() in the callback
    
    curl_easy_setopt(curl, CURLOPT_URL, "https://encrypting.host/upload");
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, eh_res_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &cbdata);

    CURLcode status = curl_easy_perform(curl);

    if (status != CURLE_OK) {
        free(cbdata.data);
        printf("Couldn't perform request: %d\n", status);

        return;
    }

    int response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

    if (response_code != 200) {
        free(cbdata.data);
        printf("Res code %d\n", response_code);

        return;
    }

    curl_easy_cleanup(curl);

    // Null termination

    cbdata.current_size++;
    cbdata.data = (char *) realloc(cbdata.data, cbdata.current_size);
    cbdata.data[cbdata.current_size - 1] = 0;

    if (extract_urls(res, &cbdata)) {
        free(cbdata.data);

        return;
    }

    free(cbdata.data);

    res->success = 1;
}
#include "config.h"

#include <string.h>
#include <stdlib.h>

#define MAX_TOKENS 1024

eh_error_t read_config(const char *path, eh_config_t *config) {
    eh_error_t err = EH_ERROR_UNKNOWN;

    config->user_key = NULL;
    config->domains = NULL;
    config->domains_len = -1;

    FILE *file = fopen(path, "r");

    if (!file) return EH_ERROR_NO_CONFIG;

    char *contents;
    size_t length = read_entire_file(file, &contents);

    fclose(file);

    jsmn_parser parser;

    jsmn_init(&parser);
    jsmntok_t tokens[MAX_TOKENS];

    int token_count = jsmn_parse(&parser, contents, length, tokens, MAX_TOKENS);

    if (token_count < 0) {
        free(contents);
        
        switch (token_count) {
            case JSMN_ERROR_INVAL:
            case JSMN_ERROR_PART:
                return EH_ERROR_BAD_JSON;
            case JSMN_ERROR_NOMEM:
                return EH_ERROR_JSON_TOO_BIG;
            default:
                return EH_ERROR_UNKNOWN;
        }
    }

    if (token_count < 1 || tokens[0].type != JSMN_OBJECT) {
        err = EH_ERROR_BAD_JSON;

        goto cleanup;
    } 

    for (int i = 1; i < token_count; i++) {
        jsmntok_t *curr = &tokens[i];
        jsmntok_t *next = &tokens[i + 1];

        if (jsoneq(contents, curr, "user_key") == 0) {
            config->user_key = json_strcpy(contents, next);
            i++;

            continue;
        }

        if (jsoneq(contents, curr, "url_style") == 0) {
            i++;

            if (jsoneq(contents, next, "query") == 0) {
                config->url_style = URL_STYLE_QUERY;
                continue;
            }

            if (jsoneq(contents, next, "param") == 0) {
                config->url_style = URL_STYLE_PARAM;
                continue;
            }

            if (jsoneq(contents, next, "embed") == 0) {
                config->url_style = URL_STYLE_EMBED;
                continue;
            }

            if (jsoneq(contents, next, "fake_link") == 0) {
                config->url_style = URL_STYLE_FAKE_LINK;
                continue;
            }

            err = EH_ERROR_BAD_URL_STYLE;

            goto cleanup;
        }

        if (jsoneq(contents, curr, "domains") == 0) {
            if (next->type != JSMN_ARRAY) {
                err = EH_ERROR_BAD_JSON;

                goto cleanup;
            }

            config->domains_len = (size_t) next->size;
            config->domains = (char **) malloc(sizeof(char *) * config->domains_len);

            for (int j = 0; j < next->size; j++) {
                jsmntok_t *curr_element = &tokens[i + j + 2];

                if (curr_element->type != JSMN_STRING) {
                    err = EH_ERROR_BAD_JSON;

                    goto cleanup;
                }

                config->domains[j] = json_strcpy(contents, curr_element);
            }

            i += next->size + 1;
        }
    }

    return EH_OK;

cleanup:
    if (config->user_key != NULL) free(config->user_key);
    if (config->domains_len != -1) free(config->domains);
    
    free(contents);

    return err;
}

const char *url_style_as_string(eh_url_style_t url_style) {
    switch (url_style) {
        case URL_STYLE_QUERY:
            return "query";
        case URL_STYLE_PARAM:
            return "param";
        case URL_STYLE_EMBED:
            return "embed";
        case URL_STYLE_FAKE_LINK:
            return "fakelink";
        default:
            return NULL;
    }
}
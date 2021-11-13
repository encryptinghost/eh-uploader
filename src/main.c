#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <curl/curl.h>

#include "config/config.h"
#include "req/req.h"
#include "util/util.h"

int main(int argc, char **argv) {
    eh_config_t config;

#ifdef _WIN32
    char *user_home = getenv("USERPROFILE");
#else
    char *user_home = getenv("HOME");
#endif

    char *end_part = "/.ehconfig.json";

    char *config_path = (char *) malloc(strlen(user_home) + strlen(end_part) + 1);

    sprintf(config_path, "%s%s", user_home, end_part);

    eh_error_t err = read_config(config_path, &config);

    if (err == EH_ERROR_NO_CONFIG) {
        printf("No config was found. Please create one.\n");

        return 1;
    }

    if (err) {
        fprintf(stderr, "Error reading the config: %d\n", err);
        return 1;
    }

    srand((unsigned int) time(NULL));

    char key[15];
    random_string(key, 14);

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    eh_req_t req;
    eh_res_t res;

    req.config = &config;
    req.encryption_key = key;
    req.file_path = argv[1];

    eh_upload_file(&req, &res);

    printf("URL: %s\nDeletion URL: %s\n", res.url, res.deletion_url);

    free(res.url);
    free(res.deletion_url);

    return 0;
}
#include "util.h"

#define CHUNK_SIZE 1024

static const char *charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static const int charset_length = 63;

char *random_string(char *str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        str[i] = charset[rand() % (charset_length - 1)];
    }

    str[size] = 0;

    return str;
}

// jsoneq taken from https://github.com/zserge/jsmn/blob/master/example/simple.c

int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}


char *json_strcpy(const char *json, jsmntok_t *tok) {
    size_t len = tok->end - tok->start + 1;

    char *str = (char *) malloc(len);
    strncpy(str, json + tok->start, len);

    str[len - 1] = '\0';

    return str;
}

size_t read_entire_file(FILE *file, char **dest) {
    *dest = (char *) malloc(1);

    size_t total_bytes_read = 0;

    do {
        *dest = (char *) realloc(*dest, total_bytes_read + CHUNK_SIZE);
        total_bytes_read += fread(*dest + total_bytes_read, 1, CHUNK_SIZE, file);
    } while (!feof(file));

    return total_bytes_read;
}

int is_alphanum(const char *str) {
    for (int i = 0; str[i] != 0; i++) {
        char c = str[i];

        if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && (c < '0' || c > '9')) return 0;
    }

    return 1;
}

char *get_config_path() {
    #ifdef _WIN32
    char *user_home = getenv("USERPROFILE");
#else
    char *user_home = getenv("HOME");
#endif

    char *end_part = "/.ehconfig.json";

    char *config_path = (char *) malloc(strlen(user_home) + strlen(end_part) + 1);

    sprintf(config_path, "%s%s", user_home, end_part);

    return config_path;
}
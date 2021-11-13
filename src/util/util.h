#if !defined(EH_UPLOADER_UTIL_H)
#define EH_UPLOADER_UTIL_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define JSMN_STATIC

#include <jsmn/jsmn.h>

char *random_string(char *str, size_t size);
int is_alphanum(const char *str);

int jsoneq(const char *json, jsmntok_t *tok, const char *s);
char *json_strcpy(const char *json, jsmntok_t *tok);

size_t read_entire_file(FILE *file, char **dest);

#endif // EH_UPLOADER_UTIL_H

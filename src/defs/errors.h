#if !defined(EH_UPLOADER_ERRORS_H)
#define EH_UPLOADER_ERRORS_H

enum eh_error_e {
    EH_OK = 0,
    EH_ERROR_UNKNOWN,
    EH_ERROR_BAD_JSON,
    EH_ERROR_JSON_TOO_BIG,
    EH_ERROR_BAD_URL_STYLE,
    EH_ERROR_NO_CONFIG
};

typedef enum eh_error_e eh_error_t;

#endif // EH_UPLOADER_ERRORS_H

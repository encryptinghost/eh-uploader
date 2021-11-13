#if !defined(EH_UPLOADER_URL_STYLE_H)
#define EH_UPLOADER_URL_STYLE_H

enum eh_url_style_e {
    URL_STYLE_QUERY,
    URL_STYLE_PARAM,
    URL_STYLE_EMBED,
    URL_STYLE_FAKE_LINK
};

typedef enum eh_url_style_e eh_url_style_t;

#endif // EH_UPLOADER_URL_STYLE_H

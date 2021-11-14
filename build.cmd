set LIBCURL=E:\Libraries\curl-7.80.0-win32-mingw
gcc -o eh-uploader src/main.c src/config/config.c src/req/req.c src/req/reqbuilder.c ^
    src/req/res.c src/util/util.c -Ideps -I"%LIBCURL%\include" -L"%LIBCURL%\lib" -lcurl
cmake_minimum_required(VERSION 3.20)
project(eh_uploader)

set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)

include_directories(deps)

add_executable(eh_uploader
        deps/jsmn/jsmn.h
        src/config/config.c
        src/config/config.h
        src/defs/errors.h
        src/defs/url_style.h
        src/req/req.c
        src/req/req.h
        src/req/reqbuilder.c
        src/req/reqbuilder.h
        src/req/res.c
        src/req/res.h
        src/util/util.c
        src/util/util.h
        src/main.c)

target_include_directories(eh_uploader PUBLIC ${CURL_INCLUDE_DIR})
target_link_libraries(eh_uploader ${CURL_LIBRARIES})

#include <stdio.h>
#include <sck_core.h>

extern sck_module_init     __start_modules_init;
extern sck_module_handler  __start_modules_handler;

extern sck_module_init     __stop_modules_init;
extern sck_module_handler  __stop_modules_handler;

void sck_modules_init() {
    for (sck_module_init *fn = &__start_modules_init; fn < &__stop_modules_init; ++fn) {
        (*fn)();
    }
}

void sck_modules_handler(sck_http_request_t *request, sck_http_response_t *response) {
    for (sck_module_handler *fn = &__start_modules_handler; fn < &__stop_modules_handler; ++fn) {
        (*fn)(request, response);
    }
}
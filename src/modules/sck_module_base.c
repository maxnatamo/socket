#include <stdio.h>
#include <sck_core.h>

static void sck_module_base_init() {
}

static int sck_module_base_handler(sck_http_request_t *request, sck_http_response_t *response) {
    return SCK_MODULE_REQUEST_NOT_HANDLED;
}

SCK_DEFINE_MOD(sck_module_base_init, sck_module_base_handler);
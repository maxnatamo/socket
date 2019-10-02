#include <stdio.h>
#include <sck_core.h>

/*
 * Module-initialization function.
 * 
 * This function is called, before any requests are handled,
 * even before the socket is been binded.
 * 
 * This function does not expect any parameters.
 */
static void sck_module_base_init() {
}

/*
 * Module-handler function.
 * 
 * This function is called after a request is handled and the response is created.
 * You're not expected to change the current parameters of the response/request,
 * but nothing is holding you back.
 * 
 * This function expects a sck_http_request_t * and a sck_http_response_t * as parameters.
 */
static void sck_module_base_handler(sck_http_request_t *request, sck_http_response_t *response) {
}

/*
 * Module definition.
 * 
 * This defines the init-function and the handler-function.
 * First parameter is the module-init function, and the second parameter is the module-handler function.
 */
SCK_DEFINE_MOD(sck_module_base_init, sck_module_base_handler);
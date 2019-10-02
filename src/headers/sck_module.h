#ifndef SCK_MOD_H
#define SCK_MOD_H

#define SCK_MODULE_REQUEST_HANDLED        0
#define SCK_MODULE_REQUEST_NOT_HANDLED    1

typedef void(* sck_module_init)();
typedef void(* sck_module_handler)(sck_http_request_t *, sck_http_response_t *);

// Thanks, Anon!
// /g/thread/72914952#p72918872
#define SCK_DEFINE_MOD(init,handler) \
    __attribute__((__section__("modules_init")))    sck_module_init    __modules_init_##init    = init; \
    __attribute__((__section__("modules_handler"))) sck_module_handler __modules_handler_##init = handler;

/*
 * Run all module-init-functions.
 * 
 * Returns: void
 */
void sck_modules_init();

/*
 * Run all module-handle-functions,
 * with both the HTTP-request and HTTP-response.
 * 
 * Returns: void
 */
void sck_modules_handler(sck_http_request_t *, sck_http_response_t *);

#endif
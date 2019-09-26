#ifndef SCK_MOD_H
#define SCK_MOD_H

typedef void(* sck_module_init)();
typedef void(* sck_module_handler)(sck_http_request_t *, sck_http_response_t *);

#define SCK_DEFINE_MOD(init,handler) \
    __attribute__((__section__("modules_init")))    sck_module_init    __modules_init_##init    = init; \
    __attribute__((__section__("modules_handler"))) sck_module_handler __modules_handler_##init = handler;

int sck_modules_init();
void sck_modules_handler(sck_http_request_t *, sck_http_response_t *);

#endif
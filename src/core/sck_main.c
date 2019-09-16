#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>   // sockaddr_in

#include <sck_types.h>

int main(int argc, char *argv[])
{
    int err = 0;
    struct sck_server_t server;
    struct sockaddr_in addr;

    err = (server.listen_fd = socket(AF_INET, SOCK_STREAM, 0));
    if(err == -1) {
        fprintf(stderr, "ERROR: Failed to initialize socket. Error code: %s\n", strerror(errno));
    }

    addr.sin_family        = AF_INET;
    addr.sin_addr.s_addr   = htonl(INADDR_ANY);
    addr.sin_port          = htons(4444);

    err = bind(server.listen_fd, (struct sockaddr *) &addr, sizeof(addr));
    if(err == -1) {
        fprintf(stderr, "ERROR: Failed to bind socket. Error code: %s\n", strerror(errno));
    }

    err = listen(server.listen_fd, 50);
    if(err == -1) {
        fprintf(stderr, "ERROR: Cannot listen to socket. Error code: %s\n", strerror(errno));
    }

    for(;;) {
        int err = 0;
        int conn_fd;
        socklen_t client_len;
        struct sockaddr_in client_addr;

        client_len = sizeof(client_addr);

        err = (conn_fd = accept(server.listen_fd, (struct sockaddr*)&client_addr, &client_len));
        if(err == -1) {
            fprintf(stderr, "ERROR: Failed to accept connection. Error code: %s\n", strerror(errno));
        }

        printf("Client connected!\n");

        char *http_response = "HTTP/1.1 200 OK\r\n"
                                "Content-Length: 42\r\n"
                                "Content-Type: text/html"
                                "\r\n"
                                "<html><body><h1>Success</h1></body></html>\r\n";

        // Send HTTP response
        err = write(conn_fd, http_response, strlen(http_response));
        if(err == -1) {
            fprintf(stderr, "ERROR: Couldn't respond to connection. Error code: %s\n", strerror(errno));
        }

        err = close(conn_fd);
        if(err == -1) {
            fprintf(stderr, "ERROR: Couldn't close connection. Error code: %s\n", strerror(errno));
        }
    }

    return 0;
}
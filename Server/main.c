#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 4444

int main() {

    int opt = 1;
    char message[1024] = "Message from server";
    struct sockaddr_in address;

    printf("Tcp socket server ... \n");

    // create socket
    int server_socket, addrlen, new_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (server_socket == -1) {
        perror("create socket failed!");
        return EXIT_FAILURE;
    }

    int set_socket_option = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (set_socket_option == -1) {
        perror("set socket option failed!");
        return EXIT_FAILURE;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);
    addrlen = sizeof(address);

    int bind_socket_status = bind(server_socket, (struct sockaddr_in *) &address, sizeof(address));
    if (bind_socket_status == -1) {
        perror("bind socket failed!");
        return EXIT_FAILURE;
    }

    int listen_status = listen(server_socket, 3);
    if (listen_status == -1) {
        perror("socket listen failed!");
        return EXIT_FAILURE;
    }

    if ((new_socket = accept(server_socket, (struct sockaddr *) &address,
                             (socklen_t *) &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    send(new_socket, message, strlen(message), 0);
    printf("message sent\n");

    return EXIT_SUCCESS;
}

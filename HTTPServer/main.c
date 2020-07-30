#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define SERVER_PORT 8888

int main() {

    printf("Starting http server on port %d ... \n", SERVER_PORT);

    FILE *html_data;
    html_data = fopen("/media/anonymous/Information/Project/C/CSocket/HTTPServer/index.html", "r");
    if (!html_data) {
        perror("fopen");
    }

    char response_data[1024];
    fgets(response_data, 1024, html_data);

    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
    strcat(http_header, response_data);

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (server_socket == -1) {
        perror("create socket failed!");
        return EXIT_FAILURE;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

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

    int client_socket;
    while (1) {
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);

    }

    return EXIT_SUCCESS;

}

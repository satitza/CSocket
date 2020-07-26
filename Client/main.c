#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {


    printf("Tcp socket client ... \n");

    // create socket [IPv4], [use segment not data gram], [protocol tcp]
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (network_socket == -1) {
        perror("create socket failed!");
        return EXIT_FAILURE;
    }
    printf("create socket success.\n");

    // specify address for socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(4444);
    server_address.sin_addr.s_addr = INADDR_ANY;
    printf("size of server_address struct : %d byte\n", sizeof(server_address));

    int connection_status = connect(network_socket, (struct sockaddr_in *) &server_address, sizeof(server_address));
    if (connection_status == -1) {
        perror("socket connect failed!");
        return EXIT_FAILURE;
    }
    printf("socket connect success.\n");


    return EXIT_SUCCESS;
}

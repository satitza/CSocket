#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_ADDRESS "192.168.0.3"
#define SERVER_PORT  4444


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
    server_address.sin_family = AF_INET; // use IPv4
    server_address.sin_port = htons(SERVER_PORT); // connect to port 4444

    // convert ip address from string to binary network format add check.
    if (inet_pton(AF_INET, SERVER_ADDRESS, &server_address.sin_addr) <= 0) {
        printf("Invalid address %s Address not supported\n", SERVER_ADDRESS);
        return EXIT_FAILURE;
    }
    printf("size of server_address struct : %d byte\n", sizeof(server_address));

    int connection_status = connect(network_socket, (struct sockaddr_in *) &server_address, sizeof(server_address));
    if (connection_status == -1) {
        perror("socket connect failed!");
        return EXIT_FAILURE;
    }
    printf("socket connect success.\n");

    // receive data from server
    char buffer[1024];
    printf("size of buffer : %d byte\n", sizeof(buffer));
    recv(network_socket, &buffer, sizeof(buffer), 0);
    printf("message from server : %s\n", buffer);

    return EXIT_SUCCESS;
}

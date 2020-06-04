#include "../header.hpp"

int     main()
{
    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    printf("Client created.\n");
    struct sockaddr_in addrClient;
    addrClient.sin_addr.s_addr = inet_addr("192.168.1.15");
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(30002);
    connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient));
    printf("Client connected.\n");

    while(1)
    {
        std::string client_input;
        getline(std::cin, client_input);
        send(socketClient, client_input.c_str(), client_input.size() + 1, 0);
    }
    close(socketClient);
    return(0);
}
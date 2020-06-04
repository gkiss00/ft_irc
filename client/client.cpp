#include "../header.hpp"

int max_socket = 0;

int     main()
{
    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrClient;
    addrClient.sin_addr.s_addr = inet_addr("192.168.1.15");
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(30002);
    printf("no connected\n");
    connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient));
    printf("connected\n");

    max_socket = socketClient + 1;

    fd_set current_sockets, copy;
    FD_ZERO(&current_sockets);
    FD_SET(socketClient, &current_sockets);

    while(1)
    {
        int socket_count;

        copy = current_sockets;
        if ((socket_count = select(max_socket + 1, &copy, NULL, NULL, NULL)) == -1)
            std::cout << "Select error" << std::endl;
        for (int i = 0; i <= max_socket; ++i)
        {
            if (FD_ISSET(i, &copy))
            {
                if (i == socketClient)
                {
                    char buff[4000];

                    //ft_fill_zero(buff, 4001);
                    recv(socketClient, buff, 4001, 0);
                    std::cout << buff << std::endl;
                }
            }
        }
    }
    close(socketClient);
    return(0);
}
#include "header.hpp"

std::string HOST;
std::string PORT_NETWORK;
std::string PASSWORD_NETWORK;
std::string PORT;
std::string PASSWORD;
fd_set current_sockets;
int max_socket = 0;


int     accept_new_connexion(int server_socket)
{
    int client_socket;
    struct sockaddr_in client_address;
    socklen_t csize = sizeof(client_address);

    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &csize);
    if (client_socket == -1)
        std::cout << "Connexion with client failed" << std::endl;
    std::cout << "accepted : client " <<  client_socket << std::endl;
    return (client_socket);
}

void add_new_client(int server_socket)
{
    int client_socket;
    if ((client_socket = accept_new_connexion(server_socket)) != -1)
    {
        FD_SET(client_socket, &current_sockets);
        if(client_socket > max_socket)
            max_socket = client_socket + 1;
    }
}

int     init_socket_server()
{
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServer == -1)
        std::cout << "We have got a socket problem" << std::endl;
    struct sockaddr_in addrServer;

    addrServer.sin_addr.s_addr = inet_addr("192.168.1.61");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(30002);

    if (bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer)) == -1)
        std::cout << "Bind failed" << std::endl;
    printf("bind %d\n", socketServer);
    return (socketServer);
}

void send_message_to_all(int i, fd_set copy, int server_socket)
{
    char buff[4001];
    ft_fill_zero(buff, 4001);
    if (recv(i, buff, 4000, 0) == -1)
    {
        FD_CLR(i, &current_sockets);
        close(i);
    }
    else
    {
        for(int j = 0; j <= max_socket; ++j)
        {
            if (FD_ISSET(i, &copy))
            {
                if (j != i && j != server_socket)
                    send(j, buff, 4001, 0);
            }
        }
    }
}

int     main()
{
    int server_socket = init_socket_server();
    if (server_socket == -1)
        return ;
    max_socket = server_socket + 1;

    fd_set copy;
    FD_ZERO(&current_sockets);
    FD_SET(server_socket, &current_sockets);
    
    listen(server_socket, 0);
    printf("listening\n");

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
                if (i == server_socket)
                    add_new_client(server_socket);
                else
                    send_message_to_all(i, copy, server_socket);
            }
        }
    }
    close(server_socket);
    return(0);
}
#include "header.hpp"

std::string HOST;
std::string PORT_NETWORK;
std::string PASSWORD_NETWORK;
std::string PORT;
std::string PASSWORD;
fd_set      current_sockets;
int         max_socket;


int     accept_new_connexion(int server_socket)
{
    int                 client_socket;
    struct sockaddr_in  client_address;
    socklen_t           csize = sizeof(client_address);

    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &csize)) == -1)
    {
        std::cout << "Connexion with client failed." << std::endl;
        return (-1);
    }
    std::cout << "Connexion with client succeed." << std::endl;
    return (client_socket);
}

void add_new_client(int server_socket)
{
    int client_socket;

    if ((client_socket = accept_new_connexion(server_socket)) == -1)
    {
        std::cout << "Could not add a new client." << std::endl;
        return ;
    }
    std::cout << "Client #" << client_socket <<  " has been added to the server." << std::endl;
    FD_SET(client_socket, &current_sockets);
    if(client_socket > max_socket)
        max_socket = client_socket + 1;
}

int     init_socket_server()
{
    int                 socketServer;
    struct sockaddr_in  addrServer;
    
    if ((socketServer = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        std::cout << "We have got a socket problem, quitting." << std::endl;
        return (-1);
    }
    addrServer.sin_addr.s_addr = inet_addr("192.168.1.15");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(30002);
    if (bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer)) == -1)
    {
        std::cout << "Bind failed, quitting." << std::endl;
        return (-1);
    }
    std::cout << "Bind #" << socketServer <<  " succeed." << std::endl;
    return (socketServer);
}

void send_message_to_all(int i, fd_set copy, int server_socket)
{
    char buff[BUFFER_SIZE + 1];

    ft_fill_zero(buff, BUFFER_SIZE + 1);
    if (recv(i, buff, BUFFER_SIZE, 0) == -1)
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
                    send(j, buff, BUFFER_SIZE + 1, 0);
            }
        }
    }
}

int     main(int argc, char **argv)
{
    t_data  data;
    int     server_socket;
    fd_set  copy;
    int     socket_count;
    
    if (check_input(argc, argv, &data) == -1)
        return (EXIT_FAILURE);
    if ((server_socket = init_socket_server()) == -1)
        return (EXIT_FAILURE);
    std::cout << "Server has been created." << std::endl;
    max_socket = server_socket + 1;

    FD_ZERO(&current_sockets);
    FD_SET(server_socket, &current_sockets);
    
    listen(server_socket, 0);
    std::cout << "Server is listenning." << std::endl;

    while(1)
    {
        copy = current_sockets;
        if ((socket_count = select(max_socket + 1, &copy, NULL, NULL, NULL)) == -1)
        {
            std::cout << "Select error, quitting." << std::endl;
            break;
        }
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
    std::cout << "Server has been closed." << std::endl;
    return(0);
}
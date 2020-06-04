#include "header.hpp"

int     check_port(std::string port_temp)
{
    int port;

    try
    {
        port = std::stoi(port_temp);
    }
    catch (std::exception const &e)
    {
        return (-1);
    }
    return (port);
}

int     check_password(std::string password)
{
    for (int i = 0; i < password.size(); ++i)
    {
        if (password.at(i) < 32 || password.at(i) > 126)
            return (-1);
    }
    return (0);
}

int     check_arg_3(char **argv, t_data *data)
{
    data->isArg1Provided = false;
    if ((data->port = check_port(argv[1])) == -1)
    {
        std::cout << "Numéro de port invalid." << std::endl;
        return (-1);
    }
    data->password = argv[2];
    if (check_password(data->password) == -1)
    {
        std::cout << "Password invalid." << std::endl;
        return (-1);
    }

    std::cout << "A server will be created." << std::endl;
    std::cout << "The server will listenning on port #" << data->port << " and the password will be '" << data->password << "'." << std::endl << std::endl;
    return (0);
}

int     check_arg_4(char **argv, t_data *data)
{
    std::string arg1(argv[1]);

    data->isArg1Provided = true;
    data->host = arg1.substr(0, arg1.find(":"));
    arg1.erase(0, arg1.find(":") + 1);
    data->port_network = arg1.substr(0, arg1.find(":"));
    arg1.erase(0, arg1.find(":") + 1);
    data->password_network = arg1.substr(0, arg1.find(":"));
    if ((data->port = check_port(argv[2])) == -1)
    {
        std::cout << "Numéro de port invalid." << std::endl;
        return (-1);
    }
    data->password = argv[3];
    if (check_password(data->password) == -1)
    {
        std::cout << "Password invalid." << std::endl;
        return (-1);
    }

    std::cout << "We will try to connect to host '"<< data->host << "' on the port #" << data->port_network << " with the password '" << data->password_network << "'." << std::endl;
    std::cout << "The server will listenning on port #" << data->port << " and the password will be '" << data->password << "'." << std::endl << std::endl;
    return (0);
}

int     check_input(int argc, char **argv, t_data *data)
{
    if (argc == 3)
        return (check_arg_3(argv, data));
    else if(argc == 4)
        return (check_arg_4(argv, data));
    else
    {
        std::cout << "Nombre d'arguments invalide." << std::endl;
        return (-1);
    }
}
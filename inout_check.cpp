#include "header.hpp"

int     check_port(char *password)
{
    std::string arg1 = std::string(password);
    for(int i = 0; i < arg1.size(); ++i)
    {
        if (arg1.at(i) < '0' || arg1.at(i) > '9')
            return (-1);
    }
}

int     check_arg_3(char **argv)
{
    if (check_port(argv[1]) == -1)
        return (-1);
}

int     check_arg_4(char **argv)
{
    if (check_port(argv[2]) == -1)
        return (-1);
    std::string arg1 = std::string(argv[1]);

    std::string delimiter = ":";
    std::string tab[3];
    int i = 0;
    int pos = 0;
    while ((pos = arg1.find(delimiter)) != std::string::npos)
    {
        tab[i] = arg1.substr(0, pos);
        arg1.erase(0, pos + delimiter.length());
        ++i;
    }
}

int     check_nb_arg(int argc)
{
    if (argc != 3 && argc != 4)
    {
        std::cout << "Nombre d argument inavlid" << std::endl;
        return (-1);
    }
    return (0);
}

int     check_input(int argc, char **argv)
{
    if (check_nb_arg(argc) == -1)
        return (-1);
    if(argc == 3)
    {
        if (check_arg_3(argv) == -1)
            return (-1);
    }
    if(argc == 4)
    {
        if (check_arg_4(argv) == -1)
            return (-1);
    }
}
#ifndef HEADER
#define HEADER

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <signal.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <pthread.h>

#define BUFFER_SIZE 4000

typedef struct	s_data
{
    bool        isArg1Provided;
	std::string host;
    std::string port_network;
    std::string password_network;

    int         port;
    std::string password;
}				t_data;

/* --- Input --- */;
int     check_input(int argc, char **argv, t_data *data);

/* --- Utils --- */
int     ft_strlen(char *str);
void    ft_putstr(char *str);
void    ft_fill_zero(char *str, int size);

#endif
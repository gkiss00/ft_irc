#include "header.hpp"

int     ft_strlen(char *str)
{
    int     i;

    i = 0;
    if (str == NULL)
        return (-1);
    while(str[i] != '\0')
        ++i;
    return (i);
}

void    ft_putstr(char *str)
{
    write(1, str, ft_strlen(str));
}

void    ft_fill_zero(char *str, int size)
{
    for (int i = 0; i < size; ++i)
    {
        str[i] = '\0';
    }
}
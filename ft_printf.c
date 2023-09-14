
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

void ft_putbase(long long int nb, int *lenght)
{
    char *str = "0123456789abcdef";
    if (nb >= 16)
        ft_putbase((nb / 16), lenght);
    write(1, &str[nb % 16], 1);
    *lenght = *lenght + 1;
}

void ft_putnbr(long long int nb, int *lenght)
{
    if (nb < 0)
    {
        *lenght += write(1, "-", 1);
        nb = nb * -1;
    }
    if (nb >= 10)
        ft_putnbr((nb / 10), lenght);
    char c = nb % 10 + '0';
    *lenght += write(1, &c, 1);
}

void ft_putstr(char *str, int *lenght)
{
    int i;

    i = 0;
    if (!str)
        str = "(null)";
    while (str[i])
    {
        write(1, &str[i], 1);
        *lenght = *lenght + 1;
        i++;
    }
}

int ft_printf(char *format, ...)
{
    int lenght;
    int i;

    lenght = 0;
    i = 0;
    va_list pointeur;
    va_start(pointeur, format);
    
    while (format[i])
    {
        if ((format[i] == '%' && format[i + 1] == 's') || (format[i] == '%' && format[i + 1] == 'd') ||  (format[i] == '%' && format[i + 1] == 'x'))
        {
            i++;
            if (format[i] == 's')
                ft_putstr(va_arg(pointeur, char *), &lenght);
            else if (format[i] == 'd')
                ft_putnbr((long long int)va_arg(pointeur, int), &lenght);
            else if (format[i] == 'x')
                ft_putbase((long long int)va_arg(pointeur, unsigned int), &lenght);
        }
        else
        {
            write(1, &format[i], 1);
            lenght++;
        }
        i++;
    }


    return (va_end(pointeur), lenght);
}

int main (void)
{
    char *lol;
    printf("le vrai = %d\n", printf("%d%\n", -2147483648));
    printf("le faux = %d\n", ft_printf("%d%\n", -2147483648));
}
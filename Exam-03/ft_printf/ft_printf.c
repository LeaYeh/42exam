#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int ft_strlen(char *s)
{
  int i = 0;

  if (!s)
    return (0);
  while (s[i])
    i++;
  return (i);
}

void print_string(char *str, int *len)
{
  if (!str)
    str = "(null)";
  *len += write(1, str, ft_strlen(str));
}

void print_digit(long long int number, int base, int *len)
{
  const char  *tab = "0123456789abcdef";

  if (number < 0)
  {
    number *= -1;
    *len += write(1, "-", 1);
  }
  if (number / base > 0)
    print_digit(number / base, base, len);
  *len += write(1, &(tab[number % base]), 1);
}

int ft_printf(const char *format, ...)
{
  int     ret;
  va_list args;

  va_start(args, format);
  ret = 0;
  while (*format)
  {
    if (*format == '%')
    {
      format++;
      if (*format == 's' || *format == 'd' || *format == 'x')
      {
        if (*format == 's')
          print_string(va_arg(args, char *), &ret);
        else if (*format == 'd')
          print_digit(va_arg(args, long long int), 10, &ret);
        else
          print_digit(va_arg(args, unsigned int), 16, &ret);
      }
    }
    else
      ret += write(1, format, 1);
    format++;
  }
  va_end(args);
  return (ret);
}

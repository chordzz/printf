#include "main.h"

/**
 * _printf - converts formatted output and prints data.
 * @format: input string.
 *
 * Return: number of chars printed.
 */
int _printf(const char *format, ...)
{
	unsigned int i = 0, len = 0, buf_count = 0;
	va_list arguments;
	int (*function)(va_list, char *, unsigned int);
	char *buffer;

	va_start(arguments, format), buffer = malloc(sizeof(char) * 1024);
	if (!format || !buffer || (format[i] == '%' && !format[i + 1]))
		return (-1);
	if (!format[i])
		return (0);
	for (i = 0; format && format[i]; i++)
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
			{	print_buf(buffer, buf_count), free(buffer), va_end(arguments);
				return (-1);
			}
			else
			{	function = get_print_func(format, i + 1);
				if (function == NULL)
				{
					if (format[i + 1] == ' ' && !format[i + 2])
						return (-1);
					handl_buf(buffer, format[i], buf_count), len++, i--;
				}
				else
				{
					len += function(arguments, buffer, buf_count);
					i += ev_print_func(format, i + 1);
				}
			} i++;
		}
		else
			handl_buf(buffer, format[i], buf_count), len++;
		for (buf_count = len; buf_count > 1024; buf_count -= 1024)
			;
	}
	print_buf(buffer, buf_count), free(buffer), va_end(arguments);
	return (len);
}
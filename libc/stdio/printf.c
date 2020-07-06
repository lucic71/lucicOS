#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <digits.h>

static bool _print(const char* data, size_t length) {

	const unsigned char* bytes = (const unsigned char*) data;

	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;

	return true;

}

/*
 * _int_to_string:
 * ---------------
 *
 *  Because there is no heap at the moment, a reference to a char array
 *  must be passed to store the result.
 *
 *  The routine checks if the number is signed, and sets the first character
 *  of the result string to '-' if so. Else it produces a normal conversion.
 *
 *  It has two special cases: when n is 0 and when n is INT_MIN.
 *
 * @param n - Number to be converted
 * @param result - Pointer to a result char array
 *
 */

static void _int_to_string(int n, char **result) {

    if (!n) {

        (*result)[0] = '0';
        return;

    }

    if (n == INT_MIN) {

        char int_min_str[] = "-2147483648";
        memcpy(*result, int_min_str, strlen(int_min_str));

        return;

    }

    int digits = 0;
    int stop_at = 0;

    if (n >> 31) {

        n = ~n + 1;
        for (int temp = n; temp != 0; temp /= 10, digits++);

        (*result)[0] = '-';
        digits++;

        stop_at = 1;

    } else

        for(int temp = n; temp != 0; temp /= 10, digits++);

    for (int i = digits - 1, temp = n; i >= stop_at; i--) {

        (*result)[i] = (temp % 10) + '0';
        temp /= 10;

    }

}

/*
 * _int_to_hex:
 * ------------
 *
 *  Divide by 16 until n is 0, put the remainder in result and at the end
 *  reverse the result string to have the correct hexadecimal number. If
 *  n is 0 simply put the char '0' in result and return.
 *
 *  A conversion to unsigned is needed because the routine must also handle
 *  negative numbers.
 *
 *
 */

static void _int_to_hex(int n, char **result) {

    if (!n) {

        (*result)[0] = '0';
        return;

    }

    unsigned int un = n;

    for (int i = 0; un != 0; un = un / 0x10, i++) {

        unsigned char rem = un % 0x10;

        if (rem < 10)
            (*result)[i] = rem + 48;
        else
            (*result)[i] = rem + 55;

    }

    int result_sz = strlen(*result);
    for (int i = 0, k = result_sz - 1; i < (result_sz / 2); i++, k--) {

        int temp = (*result)[k];
        (*result)[k] = (*result)[i];
        (*result)[i] = temp;

    }

}

int printf(const char* restrict format, ...) {

	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {

		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {

			if (format[0] == '%')
				format++;
            
			size_t amount = 1;

			while (format[amount] && format[amount] != '%')
				amount++;

			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}

			if (!_print(format, amount))
				return -1;

			format += amount;
			written += amount;

			continue;
		}

		const char* format_begun_at = format++;

		if (*format == 'c') {

			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);

			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}

			if (!_print(&c, sizeof(c)))
				return -1;

			written++;

		} else if (*format == 's') {

			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
            
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}

			if (!_print(str, len))
				return -1;

			written += len;

		} else if (*format == 'd') {

            format++;
            int n = va_arg(parameters, int);

            char str[INT32_MAX_DIGITS + 1] = {0};
            char *str_ptr = str;

            _int_to_string(n, &str_ptr);
            size_t len = strlen(str);

			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}

			if (!_print(str, len))
				return -1;

			written += len;
            
        } else if (*format == 'x') {

            format++;
            int n = va_arg(parameters, int);

            char str[INT32_MAX_HEX_DIGITS + 1] = {};
            char *str_ptr = str;

            _int_to_hex(n, &str_ptr);
            size_t len = strlen(str);

			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}

			if (!_print(str, len))
				return -1;

			written += len;

        } else {

			format = format_begun_at;
			size_t len = strlen(format);

			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}

			if (!_print(format, len))
				return -1;

			written += len;
			format += len;

		}

	}

	va_end(parameters);
	return written;
}

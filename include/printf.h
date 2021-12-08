/*
** Unstandard-Library
** File description:
** printf
*/

#ifndef PRINTF_HPP_
#define PRINTF_HPP_

///@file printf.h

#include <iomanip>
#include <iostream>

/**
 * @namespace ustd
 * The Unstandard library
 */

///\cond
#define __USTD_PRINTF_OPEN_KEY__ '{'
#define __USTD_PRINTF_CLOSE_KEY__ '}'
#define __USTD_PRINTF_LEFT_JUSTIFY_SPECIFIER__ '-'
#define __USTD_PRINTF_FLOATING_PRECISION_SPECIFIER__ '.'
#define __USTD_PRINTF_HEXADECIMAL_SPECIFIER__ '#'
#define __USTD_PRINTF_OCTAL_SPECIFIER__ '~'
///\endcond

namespace ustd {

namespace {

    inline void _print_format_parse_specifiers(std::ostream& os, std::string& string, size_t& f)
    {
        size_t i;
        for (i = f; string[i] != __USTD_PRINTF_CLOSE_KEY__ && string[i] != '\0'; i++) {
            char c = string[i];

            if (c == __USTD_PRINTF_HEXADECIMAL_SPECIFIER__) {
                os << std::hex;
                continue;
            }
            if (c == __USTD_PRINTF_OCTAL_SPECIFIER__) {
                os << std::oct;
                continue;
            }
            if (c == __USTD_PRINTF_LEFT_JUSTIFY_SPECIFIER__) {
                os << std::left;
                continue;
            }
            if (c == __USTD_PRINTF_FLOATING_PRECISION_SPECIFIER__) {
                std::string tmp = "";
                size_t j = 0;
                for (j = i + 1; std::isdigit(string[j]); j++) {
                    tmp += string[j];
                }
                if (!tmp.empty()) {
                    os << std::setprecision(std::stoi(tmp));
                }
                i = j - 1;
                continue;
            }
            if (std::isdigit(c)) {
                std::string tmp = "";
                size_t j = 0;
                for (j = i; std::isdigit(string[j]); j++) {
                    tmp += string[j];
                }
                os << std::setw(std::stoi(tmp));
                if (string[j] != __USTD_PRINTF_CLOSE_KEY__) {
                    os << std::setfill(string[j]);
                } else {
                    os << std::setfill(' ');
                    j--;
                }
                i = j;
                continue;
            }
            f = std::string::npos;
            return;
        }
        f = i + 1;
    }

    template <typename T>
    void _print_format(std::ostream& os, std::string& string, T lastElem)
    {
        std::string copy = string;
        size_t f = string.find(__USTD_PRINTF_OPEN_KEY__);
        if (f != std::string::npos) {
            copy.erase(f);
            os << copy;
        }
        _print_format_parse_specifiers(os, string, ++f);
        if (f != std::string::npos) {
            os << lastElem;
            os << std::dec << std::right << std::setprecision(6) << std::setfill(' ');
            string.erase(0, f);
        }
        os << string;
    }

    template <typename T, typename... Ts>
    void _print_format(std::ostream& os, std::string& string, T firstElem, Ts... args)
    {
        std::string copy = string;
        size_t f = string.find(__USTD_PRINTF_OPEN_KEY__);
        if (f != std::string::npos) {
            copy.erase(f);
            os << copy;
        }
        _print_format_parse_specifiers(os, string, ++f);
        if (f != std::string::npos) {
            os << firstElem;
            os << std::dec << std::right << std::setprecision(6) << std::setfill(' ');
            string.erase(0, f);
            _print_format(os, string, args...);
        } else {
            os << string;
        }
    }

    template <typename T>
    void _print(std::ostream& os, T lastElem)
    {
        os << lastElem << std::endl;
    }

    template <typename T, typename... Ts>
    void _print(std::ostream& os, T firstElem, Ts... args)
    {
        os << firstElem << " ";
        _print(os, args...);
    }
}

/**
 * @brief Prints every argument separated by a space.
 * This function adds an std::endl at the end.
 * This function relegates to std::ostream.
 * 
 * @param args Arguments to print.
 */
template <typename... Ts>
void print(Ts... args)
{
    _print(std::cout, args...);
}

/**
 * @brief Prints arguments formatted in a modern way.
 * The format specifier is "{}", no need to specify the type.
 * This function relegates to std::ostream.
 * 
 * @param fmt The format string.
 * @param args Arguments to print.
 */
template <typename... Ts>
void printf(std::string fmt, Ts... args)
{
    _print_format(std::cout, fmt, args...);
}

/**
 * @brief Similar to printf, but adds an std::endl at the end.
 * 
 * @param fmt The format string.
 * @param args Arguments to print. 
 */
template <typename... Ts>
void lprintf(std::string fmt, Ts... args)
{
    _print_format(std::cout, fmt, args...);
    std::cout << std::endl;
}

/**
 * @brief Similar to printf, but allows to specify the std::ostream to print to.
 * 
 * @param os The std::ostream to print to.
 * @param fmt The format string.
 * @param args Arguments to print.
 */
template <typename... Ts>
void osprintf(std::ostream& os, std::string fmt, Ts... args)
{
    _print_format(os, fmt, args...);
}

/**
 * @brief A combination of osprintf and lprintf.
 * 
 * @param os The std::ostream to print to.
 * @param fmt The format string.
 * @param args Arguments to print. 
 */
template <typename... Ts>
void olprintf(std::ostream& os, std::string string, Ts... args)
{
    _print_format(os, string, args...);
    os << std::endl;
}

}

#endif /* !PRINTF_HPP_ */

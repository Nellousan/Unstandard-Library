/*
** Unstandard-Library
** File description:
** printf
*/

#ifndef PRINTF_HPP_
#define PRINTF_HPP_

///@file printf.h

#include <iostream>

/**
 * @namespace ustd
 * The Unstandard library
 */

/**
 * @brief The format specifier of printf.
 */
#define __USTD_PRINTF_KEY__ "{}"

namespace ustd {

namespace {
    template <typename T>
    void _print_format(std::ostream& os, std::string& string, T lastElem)
    {
        std::string copy = string;
        size_t f = string.find(__USTD_PRINTF_KEY__);
        size_t e = f + sizeof(__USTD_PRINTF_KEY__) - 1;
        if (f != std::string::npos) {
            copy.erase(f);
            os << copy;
            os << lastElem;
            string.erase(0, e);
        }
        os << string;
    }

    template <typename T, typename... Ts>
    void _print_format(std::ostream& os, std::string& string, T firstElem, Ts... args)
    {
        std::string copy = string;
        size_t f = string.find(__USTD_PRINTF_KEY__);
        size_t e = f + sizeof(__USTD_PRINTF_KEY__) - 1;
        if (f != std::string::npos) {
            copy.erase(f);
            os << copy;
            os << firstElem;
            string.erase(0, e);
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
 * This function relegate to std::ostream.
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

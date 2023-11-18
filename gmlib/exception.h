#ifndef _GMLIB_CRYPTO_UTILS_EXCEPTION_H
#define _GMLIB_CRYPTO_UTILS_EXCEPTION_H

#include <stdexcept>
#include <boost/stacktrace.hpp>

namespace gmlib {

class Exception : public std::exception
{
public:
    boost::stacktrace::stacktrace trace;

public:
    Exception() noexcept : std::exception{}
    {
    }

    Exception(const char* msg) noexcept : std::exception{msg}
    {
    }
};

}; // namespace gmlib

#endif
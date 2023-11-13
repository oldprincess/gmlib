#ifndef _GMLIB_CRYPTO_ERR_TRACE_H
#define _GMLIB_CRYPTO_ERR_TRACE_H

#include <spdlog/spdlog.h>

namespace gmlib {

class ErrorTrace
{
private:
    size_t      line;
    bool        err;
    const char* func;
    const char* file;

public:
    ErrorTrace(size_t line, const char* func, const char* file) noexcept
    {
        this->err  = true;
        this->line = line;
        this->func = func;
        this->file = file;
    }

    ~ErrorTrace()
    {
        try
        {
            if (this->err)
            {
                spdlog::error("gmlib catch exception\n"
                              "\tin file: {}\n"
                              "\tin line: {}\n"
                              "\tin func: {}",
                              this->file, this->line, this->func);
            }
        }
        catch(...)
        {
            std::terminate();
        }
    }

public:
    void trace(size_t line) noexcept
    {
        this->line = line;
    }

    void clear() noexcept
    {
        this->err = false;
    }
};

} // namespace gmlib

#ifdef NDEBUG

#define ErrorTrace_Begin()
#define ErrorTrace_Trace(exp) exp
#define ErrorTrace_Raise()
#define ErrorTrace_End()
#define ErrorTrace_SetNoneError()

#else

#define ErrorTrace_Begin() \
    gmlib::ErrorTrace _err_trace(__LINE__, __FUNCTION__, __FILE__)
#define ErrorTrace_Trace(exp)   \
    _err_trace.trace(__LINE__); \
    exp
#define ErrorTrace_Raise()        _err_trace.trace(__LINE__)
#define ErrorTrace_End()          _err_trace.clear()
#define ErrorTrace_SetNoneError() _err_trace.clear()

#endif

#endif
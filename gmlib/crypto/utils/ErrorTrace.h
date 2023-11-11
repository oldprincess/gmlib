#ifndef _GMLIB_CRYPTO_ERR_TRACE_H
#define _GMLIB_CRYPTO_ERR_TRACE_H

#include <ostream>
#include <iostream>

namespace gmlib {

std::ostream& ErrorTrace_get_err_fpout();
void          ErrorTrace_set_err_fpout(std::ostream& fpout);

class ErrorTrace
{
private:
    std::ostream& fpout;
    size_t        line;
    bool          err;
    const char*   func;
    const char*   file;

public:
    ErrorTrace(size_t        line,
               const char*   func,
               const char*   file,
               std::ostream& fpout = ErrorTrace_get_err_fpout()) noexcept
        : fpout(fpout)
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
                this->fpout << "[error] catch exception"
                            << ", in file: " << this->file
                            << ", in line: " << this->line
                            << ", in func: " << this->func << std::endl;
            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what();
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

#else

#define ErrorTrace_Begin() \
    gmlib::ErrorTrace _err_trace(__LINE__, __FUNCTION__, __FILE__)
#define ErrorTrace_Trace(exp)   \
    _err_trace.trace(__LINE__); \
    exp
#define ErrorTrace_Raise() _err_trace.trace(__LINE__)
#define ErrorTrace_End()   _err_trace.clear()

#endif

#endif
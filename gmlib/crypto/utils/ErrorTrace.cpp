#include "ErrorTrace.h"
#include <iostream>

namespace gmlib {

static std::ostream* g_fpout = nullptr;

std::ostream& ErrorTrace_get_err_fpout()
{
    return (g_fpout == nullptr) ? (std::cerr) : *g_fpout;
}

void ErrorTrace_set_err_fpout(std::ostream& fpout)
{
    g_fpout = &fpout;
}

} // namespace gmlib
#include <gmlib/rng/cstd_rng.h>
#include <gmlib/rng/hardware_rng/rdrand32_rng.h>
#include <gmlib/rng/hardware_rng/rdrand64_rng.h>
#include <gmlib/rng/hardware_rng/rdseed32_rng.h>
#include <gmlib/rng/hardware_rng/rdseed64_rng.h>
#include <gmlib/rng/std_rng.h>

#include <cstdio>
#include <iostream>

using namespace rng;
using namespace std;

int main()
{
    CstdRng cstd_rng;
    cout << cstd_rng.name() << ", rand int: " << cstd_rng.rand<int>() << endl;

    StdRng std_rng;
    cout << std_rng.name() << ", rand int: " << std_rng.rand<int>() << endl;

#if defined(CPU_FLAG_RDRAND)
    hardware_rng::RdrandRng_32 rdrand_rng32;
    cout << rdrand_rng32.name() << ", rand int: " << rdrand_rng32.rand<int>()
         << endl;

    hardware_rng::RdrandRng_64 rdrand_rng64;
    cout << rdrand_rng64.name() << ", rand int: " << rdrand_rng64.rand<int>()
         << endl;
#endif

#if defined(CPU_FLAG_RDSEED)
    hardware_rng::RdseedRng_32 rdseed_rng32;
    cout << rdseed_rng32.name() << ", rand int: " << rdseed_rng32.rand<int>()
         << endl;

    hardware_rng::RdseedRng_64 rdseed_rng64;
    cout << rdseed_rng64.name() << ", rand int: " << rdseed_rng64.rand<int>()
         << endl;
#endif

    cout << "rng test finish!" << endl;
    return 0;
}
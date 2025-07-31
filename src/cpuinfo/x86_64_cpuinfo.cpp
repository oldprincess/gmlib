#include <gmlib/cpuinfo/cpuinfo.h>

#if defined(__x86_64__) || defined(__amd64__) || defined(_M_X64) || \
    defined(__i386__) || defined(_M_IX86)

#include <bitset>
#include <cstring>

#if defined(_MSC_VER)

#include <intrin.h>

#else

#define __cpuid(data, level)                                            \
    __asm__ __volatile__("cpuid\n\t"                                    \
                         : "=a"(data[0]), "=b"(data[1]), "=c"(data[2]), \
                           "=d"(data[3])                                \
                         : "0"(level))

#define __cpuid_count(level, count, a, b, c, d)               \
    __asm__ __volatile__("cpuid\n\t"                          \
                         : "=a"(a), "=b"(b), "=c"(c), "=d"(d) \
                         : "0"(level), "2"(count))

void __cpuidex(int __cpuid_info[4], int __leaf, int __subleaf)
{
    __cpuid_count(__leaf, __subleaf, __cpuid_info[0], __cpuid_info[1],
                  __cpuid_info[2], __cpuid_info[3]);
}

#endif

namespace cpuinfo::x86_64 {

namespace impl {

class INTEL_InstructionSet
{
public:
    static const INTEL_InstructionSet& instance() noexcept
    {
        static INTEL_InstructionSet m;
        return m;
    }

public:
    bool cpu_supports_adx() const noexcept
    {
        return f_7_ebx_[19];
    }
    bool cpu_supports_aes() const noexcept
    {
        return f_1_ecx_[25];
    }
    bool cpu_supports_avx() const noexcept
    {
        return f_1_ecx_[28];
    }
    bool cpu_supports_avx2() const noexcept
    {
        return f_7_ebx_[5];
    }
    bool cpu_supports_bmi1() const noexcept
    {
        return f_7_ebx_[3];
    }
    bool cpu_supports_bmi2() const noexcept
    {
        return f_7_ebx_[8];
    }
    bool cpu_supports_movbe() const noexcept
    {
        return f_1_ecx_[22];
    }
    bool cpu_supports_pclmulqdq() const noexcept
    {
        return f_1_ecx_[1];
    }
    bool cpu_supports_rdrand() const noexcept
    {
        return f_1_ecx_[30];
    }
    bool cpu_supports_rdseed() const noexcept
    {
        return f_7_ebx_[18];
    }
    bool cpu_supports_sha() const noexcept
    {
        return f_7_ebx_[29];
    }
    bool cpu_supports_sse() const noexcept
    {
        return f_1_edx_[25];
    }
    bool cpu_supports_sse2() const noexcept
    {
        return f_1_edx_[26];
    }
    bool cpu_supports_sse3() const noexcept
    {
        return f_1_ecx_[0];
    }
    bool cpu_supports_sse4_1() const noexcept
    {
        return f_1_ecx_[19];
    }
    bool cpu_supports_sse4_2() const noexcept
    {
        return f_1_ecx_[20];
    }
    bool cpu_supports_ssse3() const noexcept
    {
        return f_1_ecx_[9];
    }

private:
    char            vendor_[0x20] = {0};
    char            brand_[0x40]  = {0};
    std::bitset<32> f_1_ecx_      = 0; // function id = 1
    std::bitset<32> f_1_edx_      = 0; // function id = 1
    std::bitset<32> f_7_ebx_      = 0; // function id = 7
    std::bitset<32> f_7_ecx_      = 0; // function id = 7
    std::bitset<32> f_81_ecx_     = 0; // function id = 0x80000001
    std::bitset<32> f_81_edx_     = 0; // function id = 0x80000001

    INTEL_InstructionSet()
    {
        int cpu_info[4], n_ids, n_ex_ids;
        // Calling __cpuid with 0x0 as the function_id argument
        // gets the number of the highest valid function ID.
        __cpuid(cpu_info, 0);
        n_ids = cpu_info[0];
        // Capture vendor string
        *(int*)(vendor_)     = cpu_info[1];
        *(int*)(vendor_ + 4) = cpu_info[3];
        *(int*)(vendor_ + 8) = cpu_info[2];
        // load bitset with flags for function 0x00000001
        if (n_ids >= 1)
        {
            __cpuidex(cpu_info, 1, 0);
            f_1_ecx_ = cpu_info[2];
            f_1_edx_ = cpu_info[3];
        }
        // load bitset with flags for function 0x00000007
        if (n_ids >= 7)
        {
            __cpuidex(cpu_info, 7, 0);
            f_7_ebx_ = cpu_info[1];
            f_7_ecx_ = cpu_info[2];
        }
        // Calling __cpuid with 0x80000000 as the function_id argument
        // gets the number of the highest valid extended ID.
        __cpuid(cpu_info, 0x80000000);
        n_ex_ids = cpu_info[0];

        if (n_ex_ids >= 0x80000001)
        {
            __cpuidex(cpu_info, 0x80000001, 0);
            f_81_ecx_ = cpu_info[2];
            f_81_edx_ = cpu_info[3];
        }
        if (n_ex_ids >= 0x80000004)
        {
            __cpuidex(cpu_info, 0x80000002, 0);
            std::memcpy(brand_, cpu_info, 16);
            __cpuidex(cpu_info, 0x80000003, 0);
            std::memcpy(brand_ + 16, cpu_info, 16);
            __cpuidex(cpu_info, 0x80000004, 0);
            std::memcpy(brand_ + 32, cpu_info, 16);
        }
    }
};

}; // namespace impl

#define DEFINE_FN(feature)                            \
    bool cpu_supports_##feature() noexcept            \
    {                                                 \
        return impl::INTEL_InstructionSet::instance() \
            .cpu_supports_##feature();                \
    }

} // namespace cpuinfo::x86_64

#else

#define DEFINE_FN(feature)                 \
    bool cpu_supports_##feature() noexcept \
    {                                      \
        return false;                      \
    }

#endif

namespace cpuinfo::x86_64 {

DEFINE_FN(adx);
DEFINE_FN(aes);
DEFINE_FN(avx);
DEFINE_FN(avx2);
DEFINE_FN(bmi1);
DEFINE_FN(bmi2);
DEFINE_FN(movbe);
DEFINE_FN(pclmulqdq);
DEFINE_FN(rdrand);
DEFINE_FN(rdseed);
DEFINE_FN(sha);
DEFINE_FN(sse);
DEFINE_FN(sse2);
DEFINE_FN(sse3);
DEFINE_FN(sse4_1);
DEFINE_FN(sse4_2);
DEFINE_FN(ssse3);

} // namespace cpuinfo::x86_64

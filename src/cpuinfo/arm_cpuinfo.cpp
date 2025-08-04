#include <gmlib/cpuinfo/cpuinfo.h>

#if defined(__arm__) || defined(_M_ARM)

#include <asm/hwcap.h>
#include <sys/auxv.h>

class ARM_InstructionSet
{
public:
    static const ARM_InstructionSet& instance() noexcept
    {
        static ARM_InstructionSet m;
        return m;
    }

public:
    bool cpu_supports_swp() const noexcept
    {
        return hwcaps_ & HWCAP_SWP;
    }

    bool cpu_supports_half() const noexcept
    {
        return hwcaps_ & HWCAP_HALF;
    }

    bool cpu_supports_thumb() const noexcept
    {
        return hwcaps_ & HWCAP_THUMB;
    }

    bool cpu_supports_26bit() const noexcept
    {
        return hwcaps_ & HWCAP_26BIT;
    }

    bool cpu_supports_fast_mult() const noexcept
    {
        return hwcaps_ & HWCAP_FAST_MULT;
    }

    bool cpu_supports_fpa() const noexcept
    {
        return hwcaps_ & HWCAP_FPA;
    }

    bool cpu_supports_vfp() const noexcept
    {
        return hwcaps_ & HWCAP_VFP;
    }

    bool cpu_supports_edsp() const noexcept
    {
        return hwcaps_ & HWCAP_EDSP;
    }

    bool cpu_supports_java() const noexcept
    {
        return hwcaps_ & HWCAP_JAVA;
    }

    bool cpu_supports_iwmmxt() const noexcept
    {
        return hwcaps_ & HWCAP_IWMMXT;
    }

    bool cpu_supports_crunch() const noexcept
    {
        return hwcaps_ & HWCAP_CRUNCH;
    }

    bool cpu_supports_thumbee() const noexcept
    {
        return hwcaps_ & HWCAP_THUMBEE;
    }

    bool cpu_supports_neon() const noexcept
    {
        return hwcaps_ & HWCAP_NEON;
    }

    bool cpu_supports_vfpv3() const noexcept
    {
        return hwcaps_ & HWCAP_VFPv3;
    }

    bool cpu_supports_vfpv3d16() const noexcept
    {
        return hwcaps_ & HWCAP_VFPv3D16;
    }

    bool cpu_supports_tls() const noexcept
    {
        return hwcaps_ & HWCAP_TLS;
    }

    bool cpu_supports_vfpv4() const noexcept
    {
        return hwcaps_ & HWCAP_VFPv4;
    }

    bool cpu_supports_idiva() const noexcept
    {
        return hwcaps_ & HWCAP_IDIVA;
    }

    bool cpu_supports_idivt() const noexcept
    {
        return hwcaps_ & HWCAP_IDIVT;
    }

    bool cpu_supports_vfpd32() const noexcept
    {
        return hwcaps_ & HWCAP_VFPD32;
    }

    bool cpu_supports_idiv() const noexcept
    {
        return hwcaps_ & HWCAP_IDIV;
    }

    bool cpu_supports_lpae() const noexcept
    {
        return hwcaps_ & HWCAP_LPAE;
    }

    bool cpu_supports_evtstrm() const noexcept
    {
        return hwcaps_ & HWCAP_EVTSTRM;
    }

    bool cpu_supports_aes() const noexcept
    {
        return hwcaps_ & HWCAP2_AES;
    }

    bool cpu_supports_pmull() const noexcept
    {
        return hwcaps_ & HWCAP2_PMULL;
    }

    bool cpu_supports_sha1() const noexcept
    {
        return hwcaps_ & HWCAP2_SHA1;
    }

    bool cpu_supports_sha2() const noexcept
    {
        return hwcaps_ & HWCAP2_SHA2;
    }

    bool cpu_supports_crc32() const noexcept
    {
        return hwcaps_ & HWCAP2_CRC32;
    }

private:
    unsigned long hwcaps_;
    unsigned long hwcaps2_;

    ARM_InstructionSet()
    {
        hwcaps_  = getauxval(AT_HWCAP);
        hwcaps2_ = getauxval(AT_HWCAP2);
    }
};

#define DEFINE_FN(feature)                                              \
    bool cpu_supports_##feature() noexcept                              \
    {                                                                   \
        return ARM_InstructionSet::instance().cpu_supports_##feature(); \
    }

#else

#define DEFINE_FN(feature)                 \
    bool cpu_supports_##feature() noexcept \
    {                                      \
        return false;                      \
    }

#endif

namespace cpuinfo::arm {

DEFINE_FN(swp);
DEFINE_FN(half);
DEFINE_FN(thumb);
DEFINE_FN(26bit);
DEFINE_FN(fast_mult);
DEFINE_FN(fpa);
DEFINE_FN(vfp);
DEFINE_FN(edsp);
DEFINE_FN(java);
DEFINE_FN(iwmmxt);
DEFINE_FN(crunch);
DEFINE_FN(thumbee);
DEFINE_FN(neon);
DEFINE_FN(vfpv3);
DEFINE_FN(vfpv3d16);
DEFINE_FN(tls);
DEFINE_FN(vfpv4);
DEFINE_FN(idiva);
DEFINE_FN(idivt);
DEFINE_FN(vfpd32);
DEFINE_FN(idiv);
DEFINE_FN(lpae);
DEFINE_FN(evtstrm);

DEFINE_FN(aes);
DEFINE_FN(pmull);
DEFINE_FN(sha1);
DEFINE_FN(sha2);
DEFINE_FN(crc32);

}; // namespace cpuinfo::aarch64
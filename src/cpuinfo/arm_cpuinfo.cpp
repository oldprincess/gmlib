#include <gmlib/cpuinfo/cpuinfo.h>

#if defined(__aarch64__) || defined(__arm64__) || defined(_M_ARM64) || \
    defined(__arm__) || defined(_M_ARM)

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
    bool cpu_supports_fp() const noexcept
    {
        return hwcaps_ & HWCAP_FP;
    }

    bool cpu_supports_asimd() const noexcept
    {
        return hwcaps_ & HWCAP_ASIMD;
    }

    bool cpu_supports_evtstrm() const noexcept
    {
        return hwcaps_ & HWCAP_EVTSTRM;
    }

    bool cpu_supports_aes() const noexcept
    {
        return hwcaps_ & HWCAP_AES;
    }

    bool cpu_supports_pmull() const noexcept
    {
        return hwcaps_ & HWCAP_PMULL;
    }

    bool cpu_supports_sha1() const noexcept
    {
        return hwcaps_ & HWCAP_SHA1;
    }

    bool cpu_supports_sha2() const noexcept
    {
        return hwcaps_ & HWCAP_SHA2;
    }

    bool cpu_supports_crc32() const noexcept
    {
        return hwcaps_ & HWCAP_CRC32;
    }

    bool cpu_supports_atomics() const noexcept
    {
        return hwcaps_ & HWCAP_ATOMICS;
    }

    bool cpu_supports_fphp() const noexcept
    {
        return hwcaps_ & HWCAP_FPHP;
    }

    bool cpu_supports_asimdhp() const noexcept
    {
        return hwcaps_ & HWCAP_ASIMDHP;
    }

    bool cpu_supports_cpuid() const noexcept
    {
        return hwcaps_ & HWCAP_CPUID;
    }

    bool cpu_supports_asimdrdm() const noexcept
    {
        return hwcaps_ & HWCAP_ASIMDRDM;
    }

    bool cpu_supports_jscvt() const noexcept
    {
        return hwcaps_ & HWCAP_JSCVT;
    }

    bool cpu_supports_fcma() const noexcept
    {
        return hwcaps_ & HWCAP_FCMA;
    }

    bool cpu_supports_lrcpc() const noexcept
    {
        return hwcaps_ & HWCAP_LRCPC;
    }

    bool cpu_supports_dcpop() const noexcept
    {
        return hwcaps_ & HWCAP_DCPOP;
    }

    bool cpu_supports_sha3() const noexcept
    {
        return hwcaps_ & HWCAP_SHA3;
    }

    bool cpu_supports_sm3() const noexcept
    {
        return hwcaps_ & HWCAP_SM3;
    }

    bool cpu_supports_sm4() const noexcept
    {
        return hwcaps_ & HWCAP_SM4;
    }

    bool cpu_supports_asimddp() const noexcept
    {
        return hwcaps_ & HWCAP_ASIMDDP;
    }

    bool cpu_supports_sha512() const noexcept
    {
        return hwcaps_ & HWCAP_SHA512;
    }

    bool cpu_supports_sve() const noexcept
    {
        return hwcaps_ & HWCAP_SVE;
    }

    bool cpu_supports_asimdfhm() const noexcept
    {
        return hwcaps_ & HWCAP_ASIMDFHM;
    }

    bool cpu_supports_dit() const noexcept
    {
        return hwcaps_ & HWCAP_DIT;
    }

    bool cpu_supports_uscat() const noexcept
    {
        return hwcaps_ & HWCAP_USCAT;
    }

    bool cpu_supports_ilrcpc() const noexcept
    {
        return hwcaps_ & HWCAP_ILRCPC;
    }

    bool cpu_supports_flagm() const noexcept
    {
        return hwcaps_ & HWCAP_FLAGM;
    }

    bool cpu_supports_ssbs() const noexcept
    {
        return hwcaps_ & HWCAP_SSBS;
    }

    bool cpu_supports_sb() const noexcept
    {
        return hwcaps_ & HWCAP_SB;
    }

    bool cpu_supports_paca() const noexcept
    {
        return hwcaps_ & HWCAP_PACA;
    }

    bool cpu_supports_pacg() const noexcept
    {
        return hwcaps_ & HWCAP_PACG;
    }

private:
    unsigned long hwcaps_;

    ARM_InstructionSet()
    {
        hwcaps_ = getauxval(AT_HWCAP);
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

DEFINE_FN(fp);
DEFINE_FN(asimd);
DEFINE_FN(evtstrm);
DEFINE_FN(aes);
DEFINE_FN(pmull);
DEFINE_FN(sha1);
DEFINE_FN(sha2);
DEFINE_FN(crc32);
DEFINE_FN(atomics);
DEFINE_FN(fphp);
DEFINE_FN(asimdhp);
DEFINE_FN(cpuid);
DEFINE_FN(asimdrdm);
DEFINE_FN(jscvt);
DEFINE_FN(fcma);
DEFINE_FN(lrcpc);
DEFINE_FN(dcpop);
DEFINE_FN(sha3);
DEFINE_FN(sm3);
DEFINE_FN(sm4);
DEFINE_FN(asimddp);
DEFINE_FN(sha512);
DEFINE_FN(sve);
DEFINE_FN(asimdfhm);
DEFINE_FN(dit);
DEFINE_FN(uscat);
DEFINE_FN(ilrcpc);
DEFINE_FN(flagm);
DEFINE_FN(ssbs);
DEFINE_FN(sb);
DEFINE_FN(paca);
DEFINE_FN(pacg);

}; // namespace cpuinfo::arm
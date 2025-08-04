#include <gmlib/cpuinfo/cpuinfo.h>

#if defined(__aarch64__) || defined(__arm64__) || defined(_M_ARM64)

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

    bool cpu_supports_dcpodp() const noexcept
    {
        return hwcaps_ & HWCAP2_DCPODP;
    }

    bool cpu_supports_sve2() const noexcept
    {
        return hwcaps_ & HWCAP2_SVE2;
    }

    bool cpu_supports_sveaes() const noexcept
    {
        return hwcaps_ & HWCAP2_SVEAES;
    }

    bool cpu_supports_svepmull() const noexcept
    {
        return hwcaps_ & HWCAP2_SVEPMULL;
    }

    bool cpu_supports_svebitperm() const noexcept
    {
        return hwcaps_ & HWCAP2_SVEBITPERM;
    }

    bool cpu_supports_svesha3() const noexcept
    {
        return hwcaps_ & HWCAP2_SVESHA3;
    }

    bool cpu_supports_svesm4() const noexcept
    {
        return hwcaps_ & HWCAP2_SVESM4;
    }

    bool cpu_supports_flagm2() const noexcept
    {
        return hwcaps_ & HWCAP2_FLAGM2;
    }

    bool cpu_supports_frint() const noexcept
    {
        return hwcaps_ & HWCAP2_FRINT;
    }

    bool cpu_supports_svei8mm() const noexcept
    {
        return hwcaps_ & HWCAP2_SVEI8MM;
    }

    bool cpu_supports_svef32mm() const noexcept
    {
        return hwcaps_ & HWCAP2_SVEF32MM;
    }

    bool cpu_supports_svef64mm() const noexcept
    {
        return hwcaps_ & HWCAP2_SVEF64MM;
    }

    bool cpu_supports_svebf16() const noexcept
    {
        return hwcaps_ & HWCAP2_SVEBF16;
    }

    bool cpu_supports_i8mm() const noexcept
    {
        return hwcaps_ & HWCAP2_I8MM;
    }

    bool cpu_supports_bf16() const noexcept
    {
        return hwcaps_ & HWCAP2_BF16;
    }

    bool cpu_supports_dgh() const noexcept
    {
        return hwcaps_ & HWCAP2_DGH;
    }

    bool cpu_supports_rng() const noexcept
    {
        return hwcaps_ & HWCAP2_RNG;
    }

    bool cpu_supports_bti() const noexcept
    {
        return hwcaps_ & HWCAP2_BTI;
    }

    bool cpu_supports_mte() const noexcept
    {
        return hwcaps_ & HWCAP2_MTE;
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

namespace cpuinfo::aarch64 {

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

DEFINE_FN(dcpodp);
DEFINE_FN(sve2);
DEFINE_FN(sveaes);
DEFINE_FN(svepmull);
DEFINE_FN(svebitperm);
DEFINE_FN(svesha3);
DEFINE_FN(svesm4);
DEFINE_FN(flagm2);
DEFINE_FN(frint);
DEFINE_FN(svei8mm);
DEFINE_FN(svef32mm);
DEFINE_FN(svef64mm);
DEFINE_FN(svebf16);
DEFINE_FN(i8mm);
DEFINE_FN(bf16);
DEFINE_FN(dgh);
DEFINE_FN(rng);
DEFINE_FN(bti);
DEFINE_FN(mte);

}; // namespace cpuinfo::aarch64
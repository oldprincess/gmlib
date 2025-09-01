#include <gmlib/cpuinfo/cpuinfo.h>

#include <cstdio>

#define TEST(fn) std::printf(#fn ": %s\n", fn() ? "true" : "false")

int main()
{
    std::puts("==================================");
    std::puts("============= X86_64 =============");
    std::puts("==================================");
    TEST(cpuinfo::x86_64::cpu_supports_adx);
    TEST(cpuinfo::x86_64::cpu_supports_aes);
    TEST(cpuinfo::x86_64::cpu_supports_avx);
    TEST(cpuinfo::x86_64::cpu_supports_avx2);
    TEST(cpuinfo::x86_64::cpu_supports_avx512bw);
    TEST(cpuinfo::x86_64::cpu_supports_avx512f);
    TEST(cpuinfo::x86_64::cpu_supports_avx512vl);
    TEST(cpuinfo::x86_64::cpu_supports_bmi1);
    TEST(cpuinfo::x86_64::cpu_supports_bmi2);
    TEST(cpuinfo::x86_64::cpu_supports_gfni);
    TEST(cpuinfo::x86_64::cpu_supports_movbe);
    TEST(cpuinfo::x86_64::cpu_supports_pclmulqdq);
    TEST(cpuinfo::x86_64::cpu_supports_rdrand);
    TEST(cpuinfo::x86_64::cpu_supports_rdseed);
    TEST(cpuinfo::x86_64::cpu_supports_sha);
    TEST(cpuinfo::x86_64::cpu_supports_sse);
    TEST(cpuinfo::x86_64::cpu_supports_sse2);
    TEST(cpuinfo::x86_64::cpu_supports_sse3);
    TEST(cpuinfo::x86_64::cpu_supports_sse4_1);
    TEST(cpuinfo::x86_64::cpu_supports_sse4_2);
    TEST(cpuinfo::x86_64::cpu_supports_ssse3);

    std::puts("==================================");
    std::puts("============= ARM ================");
    std::puts("==================================");
    TEST(cpuinfo::arm::cpu_supports_swp);
    TEST(cpuinfo::arm::cpu_supports_half);
    TEST(cpuinfo::arm::cpu_supports_thumb);
    TEST(cpuinfo::arm::cpu_supports_26bit);
    TEST(cpuinfo::arm::cpu_supports_fast_mult);
    TEST(cpuinfo::arm::cpu_supports_fpa);
    TEST(cpuinfo::arm::cpu_supports_vfp);
    TEST(cpuinfo::arm::cpu_supports_edsp);
    TEST(cpuinfo::arm::cpu_supports_java);
    TEST(cpuinfo::arm::cpu_supports_iwmmxt);
    TEST(cpuinfo::arm::cpu_supports_crunch);
    TEST(cpuinfo::arm::cpu_supports_thumbee);
    TEST(cpuinfo::arm::cpu_supports_neon);
    TEST(cpuinfo::arm::cpu_supports_vfpv3);
    TEST(cpuinfo::arm::cpu_supports_vfpv3d16);
    TEST(cpuinfo::arm::cpu_supports_tls);
    TEST(cpuinfo::arm::cpu_supports_vfpv4);
    TEST(cpuinfo::arm::cpu_supports_idiva);
    TEST(cpuinfo::arm::cpu_supports_idivt);
    TEST(cpuinfo::arm::cpu_supports_vfpd32);
    TEST(cpuinfo::arm::cpu_supports_idiv);
    TEST(cpuinfo::arm::cpu_supports_lpae);
    TEST(cpuinfo::arm::cpu_supports_evtstrm);

    TEST(cpuinfo::arm::cpu_supports_aes);
    TEST(cpuinfo::arm::cpu_supports_pmull);
    TEST(cpuinfo::arm::cpu_supports_sha1);
    TEST(cpuinfo::arm::cpu_supports_sha2);
    TEST(cpuinfo::arm::cpu_supports_crc32);

    std::puts("==================================");
    std::puts("============= AARCH64 ============");
    std::puts("==================================");

    TEST(cpuinfo::aarch64::cpu_supports_fp);
    TEST(cpuinfo::aarch64::cpu_supports_asimd);
    TEST(cpuinfo::aarch64::cpu_supports_evtstrm);
    TEST(cpuinfo::aarch64::cpu_supports_aes);
    TEST(cpuinfo::aarch64::cpu_supports_pmull);
    TEST(cpuinfo::aarch64::cpu_supports_sha1);
    TEST(cpuinfo::aarch64::cpu_supports_sha2);
    TEST(cpuinfo::aarch64::cpu_supports_crc32);
    TEST(cpuinfo::aarch64::cpu_supports_atomics);
    TEST(cpuinfo::aarch64::cpu_supports_fphp);
    TEST(cpuinfo::aarch64::cpu_supports_asimdhp);
    TEST(cpuinfo::aarch64::cpu_supports_cpuid);
    TEST(cpuinfo::aarch64::cpu_supports_asimdrdm);
    TEST(cpuinfo::aarch64::cpu_supports_jscvt);
    TEST(cpuinfo::aarch64::cpu_supports_fcma);
    TEST(cpuinfo::aarch64::cpu_supports_lrcpc);
    TEST(cpuinfo::aarch64::cpu_supports_dcpop);
    TEST(cpuinfo::aarch64::cpu_supports_sha3);
    TEST(cpuinfo::aarch64::cpu_supports_sm3);
    TEST(cpuinfo::aarch64::cpu_supports_sm4);
    TEST(cpuinfo::aarch64::cpu_supports_asimddp);
    TEST(cpuinfo::aarch64::cpu_supports_sha512);
    TEST(cpuinfo::aarch64::cpu_supports_sve);
    TEST(cpuinfo::aarch64::cpu_supports_asimdfhm);
    TEST(cpuinfo::aarch64::cpu_supports_dit);
    TEST(cpuinfo::aarch64::cpu_supports_uscat);
    TEST(cpuinfo::aarch64::cpu_supports_ilrcpc);
    TEST(cpuinfo::aarch64::cpu_supports_flagm);
    TEST(cpuinfo::aarch64::cpu_supports_ssbs);
    TEST(cpuinfo::aarch64::cpu_supports_sb);
    TEST(cpuinfo::aarch64::cpu_supports_paca);
    TEST(cpuinfo::aarch64::cpu_supports_pacg);

    TEST(cpuinfo::aarch64::cpu_supports_dcpodp);
    TEST(cpuinfo::aarch64::cpu_supports_sve2);
    TEST(cpuinfo::aarch64::cpu_supports_sveaes);
    TEST(cpuinfo::aarch64::cpu_supports_svepmull);
    TEST(cpuinfo::aarch64::cpu_supports_svebitperm);
    TEST(cpuinfo::aarch64::cpu_supports_svesha3);
    TEST(cpuinfo::aarch64::cpu_supports_svesm4);
    TEST(cpuinfo::aarch64::cpu_supports_flagm2);
    TEST(cpuinfo::aarch64::cpu_supports_frint);
    TEST(cpuinfo::aarch64::cpu_supports_svei8mm);
    TEST(cpuinfo::aarch64::cpu_supports_svef32mm);
    TEST(cpuinfo::aarch64::cpu_supports_svef64mm);
    TEST(cpuinfo::aarch64::cpu_supports_svebf16);
    TEST(cpuinfo::aarch64::cpu_supports_i8mm);
    TEST(cpuinfo::aarch64::cpu_supports_bf16);
    TEST(cpuinfo::aarch64::cpu_supports_dgh);
    TEST(cpuinfo::aarch64::cpu_supports_rng);
    TEST(cpuinfo::aarch64::cpu_supports_bti);
    TEST(cpuinfo::aarch64::cpu_supports_mte);
    return 0;
}
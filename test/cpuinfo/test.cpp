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
    TEST(cpuinfo::x86_64::cpu_supports_bmi1);
    TEST(cpuinfo::x86_64::cpu_supports_bmi2);
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
    TEST(cpuinfo::arm::cpu_supports_fp);
    TEST(cpuinfo::arm::cpu_supports_asimd);
    TEST(cpuinfo::arm::cpu_supports_evtstrm);
    TEST(cpuinfo::arm::cpu_supports_aes);
    TEST(cpuinfo::arm::cpu_supports_pmull);
    TEST(cpuinfo::arm::cpu_supports_sha1);
    TEST(cpuinfo::arm::cpu_supports_sha2);
    TEST(cpuinfo::arm::cpu_supports_crc32);
    TEST(cpuinfo::arm::cpu_supports_atomics);
    TEST(cpuinfo::arm::cpu_supports_fphp);
    TEST(cpuinfo::arm::cpu_supports_asimdhp);
    TEST(cpuinfo::arm::cpu_supports_cpuid);
    TEST(cpuinfo::arm::cpu_supports_asimdrdm);
    TEST(cpuinfo::arm::cpu_supports_jscvt);
    TEST(cpuinfo::arm::cpu_supports_fcma);
    TEST(cpuinfo::arm::cpu_supports_lrcpc);
    TEST(cpuinfo::arm::cpu_supports_dcpop);
    TEST(cpuinfo::arm::cpu_supports_sha3);
    TEST(cpuinfo::arm::cpu_supports_sm3);
    TEST(cpuinfo::arm::cpu_supports_sm4);
    TEST(cpuinfo::arm::cpu_supports_asimddp);
    TEST(cpuinfo::arm::cpu_supports_sha512);
    TEST(cpuinfo::arm::cpu_supports_sve);
    TEST(cpuinfo::arm::cpu_supports_asimdfhm);
    TEST(cpuinfo::arm::cpu_supports_dit);
    TEST(cpuinfo::arm::cpu_supports_uscat);
    TEST(cpuinfo::arm::cpu_supports_ilrcpc);
    TEST(cpuinfo::arm::cpu_supports_flagm);
    TEST(cpuinfo::arm::cpu_supports_ssbs);
    TEST(cpuinfo::arm::cpu_supports_sb);
    TEST(cpuinfo::arm::cpu_supports_paca);
    TEST(cpuinfo::arm::cpu_supports_pacg);
    return 0;
}
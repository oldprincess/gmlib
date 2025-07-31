#ifndef CPUINFO_CPUINFO_H
#define CPUINFO_CPUINFO_H

namespace cpuinfo {

namespace x86_64 {

bool cpu_supports_adx() noexcept;
bool cpu_supports_aes() noexcept;
bool cpu_supports_avx() noexcept;
bool cpu_supports_avx2() noexcept;
bool cpu_supports_bmi1() noexcept;
bool cpu_supports_bmi2() noexcept;
bool cpu_supports_movbe() noexcept;
bool cpu_supports_pclmulqdq() noexcept;
bool cpu_supports_rdrand() noexcept;
bool cpu_supports_rdseed() noexcept;
bool cpu_supports_sha() noexcept;
bool cpu_supports_sse() noexcept;
bool cpu_supports_sse2() noexcept;
bool cpu_supports_sse3() noexcept;
bool cpu_supports_sse4_1() noexcept;
bool cpu_supports_sse4_2() noexcept;
bool cpu_supports_ssse3() noexcept;

} // namespace x86_64

namespace arm {

bool cpu_supports_fp() noexcept;
bool cpu_supports_asimd() noexcept;
bool cpu_supports_evtstrm() noexcept;
bool cpu_supports_aes() noexcept;
bool cpu_supports_pmull() noexcept;
bool cpu_supports_sha1() noexcept;
bool cpu_supports_sha2() noexcept;
bool cpu_supports_crc32() noexcept;
bool cpu_supports_atomics() noexcept;
bool cpu_supports_fphp() noexcept;
bool cpu_supports_asimdhp() noexcept;
bool cpu_supports_cpuid() noexcept;
bool cpu_supports_asimdrdm() noexcept;
bool cpu_supports_jscvt() noexcept;
bool cpu_supports_fcma() noexcept;
bool cpu_supports_lrcpc() noexcept;
bool cpu_supports_dcpop() noexcept;
bool cpu_supports_sha3() noexcept;
bool cpu_supports_sm3() noexcept;
bool cpu_supports_sm4() noexcept;
bool cpu_supports_asimddp() noexcept;
bool cpu_supports_sha512() noexcept;
bool cpu_supports_sve() noexcept;
bool cpu_supports_asimdfhm() noexcept;
bool cpu_supports_dit() noexcept;
bool cpu_supports_uscat() noexcept;
bool cpu_supports_ilrcpc() noexcept;
bool cpu_supports_flagm() noexcept;
bool cpu_supports_ssbs() noexcept;
bool cpu_supports_sb() noexcept;
bool cpu_supports_paca() noexcept;
bool cpu_supports_pacg() noexcept;

} // namespace arm

} // namespace cpuinfo

#endif
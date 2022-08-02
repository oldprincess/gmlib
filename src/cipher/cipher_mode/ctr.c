#include <gmlib/cipher/mode.h>
#include <gmlib/utils.h>
#include <memory.h>

static void ctr_inc(uint8_t* r, uint8_t* cnt, int block_size) {
    uint16_t carry = 1;
    uint16_t tmp = 0;
    for (int i = block_size - 1; i >= 0; i--) {
        tmp = (uint16_t)cnt[i] + carry;
        carry = (tmp >> 8);
        r[i] = (uint8_t)(tmp & UINT8_MAX);
    }
}

/// @brief CTR模式update
void ctr_update(uint8_t* out,           // output buffer
                int* outl,              // output len
                uint8_t* in,            // input buffer
                int inl,                // input len
                CipherEncrypt encrypt,  // encrypt func
                void* cipher_key,       // cipher key
                int block_size,         // cipher block size
                uint8_t* ctr_iv,        // ctr iv
                uint8_t* ctr_buffer,    // ctr buffer
                int* ctr_bsize,         // ctr buffer size
                int ctr_mbsize          // ctr max bsize
) {
    *outl = 0;  // 初始化 outl
    while (inl > 0) {
        // 拷贝缓冲区数据
        int size = ctr_mbsize - *ctr_bsize;
        if (size > inl) {
            size = inl;
        }
        memcpy(ctr_buffer + *ctr_bsize, in, size);
        *ctr_bsize += size;  // 更新 buffer pos
        in += size;          // 更新 input ptr
        inl -= size;         // 更新 input len
        // 缓冲区是否已满
        if (*ctr_bsize == ctr_mbsize) {
            // 缓冲区填满，加密
            memcpy(out, ctr_buffer, ctr_mbsize);  // 临时拷贝
            memcpy(ctr_buffer, ctr_iv, block_size);
            for (int i = block_size; i < ctr_mbsize; i += block_size) {
                ctr_inc(ctr_buffer + i, ctr_buffer + i - block_size,
                        block_size);
            }
            ctr_inc(ctr_iv, ctr_buffer + ctr_mbsize - block_size, block_size);
            encrypt(ctr_buffer, ctr_buffer, ctr_mbsize / block_size,
                    cipher_key);
            memxor(out, out, ctr_buffer, ctr_mbsize);

            *ctr_bsize = 0;       // 清空缓冲区
            *outl += ctr_mbsize;  //更新output len
            out += ctr_mbsize;    // 更新 output ptr
        }
    }
}

/// @brief CTR模式final
void ctr_final(uint8_t* out,           // output buffer
               int* outl,              // output len
               CipherEncrypt encrypt,  // encrypt func
               void* cipher_key,       // cipher key
               int block_size,         // cipher block size
               uint8_t* ctr_iv,        // ctr iv
               uint8_t* ctr_buffer,    // ctr buffer
               int* ctr_bsize          // ctr buffer size
) {
    if (*ctr_bsize) {
        memcpy(out, ctr_buffer, *ctr_bsize);  // 临时拷贝
        // 生成 counter
        memcpy(ctr_buffer, ctr_iv, block_size);
        int size = (*ctr_bsize + block_size - 1) / block_size;  // block num
        for (int i = block_size; i < *ctr_bsize; i += block_size) {
            // cnt[i] = cnt[i-1]+1
            ctr_inc(ctr_buffer + i, ctr_buffer + i - block_size, block_size);
        }
        // encrypt
        encrypt(ctr_buffer, ctr_buffer, size, cipher_key);
        memxor(out, out, ctr_buffer, *ctr_bsize);
    }

    *outl = *ctr_bsize;  //更新output len
}

#include <gmlib/_sm4.h>

#include <iostream>
int main()
{
    std::cout << "sm4_ecb_encrypt_get_block_size   = "
              << gmlib_sm4_ecb_encrypt_get_block_size() << std::endl;
    std::cout << "sm4_ecb_encrypt_get_user_key_len = "
              << gmlib_sm4_ecb_encrypt_get_user_key_len() << std::endl;
    auto ctx = gmlib_sm4_ecb_encrypt_ctx_new();
    if (ctx == NULL)
    {
        return -1;
    }
    gmlib_sm4_ecb_encrypt_ctx_delete(ctx);
    std::cout << "test ok" << std::endl;
    return 0;
}

#ifndef ZUC_COMMON_H
#define ZUC_COMMON_H

#include <gmlib/stream/zuc.h>

/// @brief 祖冲之算法ZUC初始化
/// @param[in]  key     128比特密钥
/// @param[in]  iv      128比特初始向量
/// @param[out] zuc_ctx ZUC算法Context
void zuc_common_init(uint8_t* key, uint8_t* iv, ZUC_CTX* zuc_ctx);

/// @brief 祖冲之算法产生一节拍32比特密钥
/// @param[inout] zuc_ctx ZUC算法Context
/// @return 32比特密钥字
uint32_t zuc_common_next(ZUC_CTX* zuc_ctx);

#endif // ZUC_COMMON_H

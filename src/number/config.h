#ifndef NUMBER_CONFIG_H
#define NUMBER_CONFIG_H

#if defined(__MOVBE__) && defined(__BMI2__)
#define NUMBER_IMPL_X64
#endif

#define NUMBER_IMPL_COMMON

#endif
#ifndef _include_h
#define _include_h
#include "memwatch.h"

#define K_PRINT_LINE printf("%s:%d\n", __FILE__, __LINE__)
#define K_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)

#ifndef _DEBUG
#warning "no define _DEBUG"
#endif
#ifdef _DEBUG
#define K_DEBUG(fmt, ...) K_PRINT(fmt, ##__VA_ARGS__)
#define _DEBUG_LOG
#else
#define K_DEBUG(fmt, ...)
#endif //ifdef _DEBUG

#if defined(_DEBUG_LOG)
#define K_LOG(TYPE, fmt, ...)        \
    do                               \
    {                                \
        K_PRINT("  >[%s] :", #TYPE); \
        K_PRINT(fmt, ##__VA_ARGS__); \
    } while (0 == 1)
#else
#define K_LOG(TYPE, fmt, ...)
#endif // _DEBUG_LOG

#define K_INFOMATION(fmt, ...) K_LOG(Info, fmt, ##__VA_ARGS__)

#define K_WARNINR(fmt, ...) K_LOG(Warning, fmt, ##__VA_ARGS__)

#define K_ERROR(fmt, ...) K_LOG(Error, fmt, ##__VA_ARGS__)

#define K_SMANAGE_DATA_MIN_BUFF_SIZE ((K_FRAME_DATA_MAX_SIZE + 9) * 2)

#endif // _include_h
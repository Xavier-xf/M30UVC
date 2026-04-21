/*
 * uvc_log.h  -  轻量级 header-only 分级日志（fprintf 封装）
 *               输出到 stderr，附带时间戳 + 源文件位置。
 */
#ifndef UVC_LOG_H
#define UVC_LOG_H

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    UVC_LL_TRACE = 0,
    UVC_LL_DEBUG,
    UVC_LL_INFO,
    UVC_LL_WARN,
    UVC_LL_ERROR,
    UVC_LL_FATAL,
    UVC_LL_OFF,
} uvc_log_level_t;

#ifndef UVC_LOG_LEVEL
#define UVC_LOG_LEVEL  UVC_LL_INFO
#endif

static inline const char *uvc__lvl_tag(uvc_log_level_t lvl)
{
    switch (lvl) {
    case UVC_LL_TRACE: return "TRACE";
    case UVC_LL_DEBUG: return "DEBUG";
    case UVC_LL_INFO:  return "INFO ";
    case UVC_LL_WARN:  return "WARN ";
    case UVC_LL_ERROR: return "ERROR";
    case UVC_LL_FATAL: return "FATAL";
    default:           return "?????";
    }
}

#define UVC_LOG(lvl, fmt, ...)                                              \
    do {                                                                    \
        if ((lvl) >= UVC_LOG_LEVEL && (lvl) < UVC_LL_OFF) {                \
            struct timeval _tv;                                             \
            gettimeofday(&_tv, NULL);                                       \
            struct tm _tm;                                                  \
            localtime_r(&_tv.tv_sec, &_tm);                                \
            fprintf(stderr, "[%02d:%02d:%02d.%03ld][%s][%s:%d] " fmt "\n", \
                    _tm.tm_hour, _tm.tm_min, _tm.tm_sec,                   \
                    (long)(_tv.tv_usec / 1000),                             \
                    uvc__lvl_tag(lvl), __FILE__, __LINE__,                  \
                    ##__VA_ARGS__);                                         \
        }                                                                   \
    } while (0)

#define UVC_LOGT(fmt, ...)  UVC_LOG(UVC_LL_TRACE, fmt, ##__VA_ARGS__)
#define UVC_LOGD(fmt, ...)  UVC_LOG(UVC_LL_DEBUG, fmt, ##__VA_ARGS__)
#define UVC_LOGI(fmt, ...)  UVC_LOG(UVC_LL_INFO,  fmt, ##__VA_ARGS__)
#define UVC_LOGW(fmt, ...)  UVC_LOG(UVC_LL_WARN,  fmt, ##__VA_ARGS__)
#define UVC_LOGE(fmt, ...)  UVC_LOG(UVC_LL_ERROR, fmt, ##__VA_ARGS__)
#define UVC_LOGF(fmt, ...)  UVC_LOG(UVC_LL_FATAL, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif
#endif /* UVC_LOG_H */

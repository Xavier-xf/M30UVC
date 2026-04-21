/*
 * uvc_m30.h  -  M30 UVC 封装层公开接口
 *
 *   纯 C、线程安全，覆盖 SDK 全部功能分区：
 *     生命周期 / 设备信息 / 视频流 / 摄像头控制 /
 *     AI 人脸底库 / 识别控制 / 数据上报 / 系统维护
 *
 *   设计要点：
 *     - 不透明上下文，无全局状态
 *     - m30_open() 分阶段提交 + 完整回滚
 *     - 统一 M30_ERR_* 错误码，m30_strerror() 可读描述
 *     - 函数名用 m30_ 前缀区分通用 UVC
 */

#ifndef UVC_M30_H
#define UVC_M30_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/*  错误码                                                                   */
/* ------------------------------------------------------------------------ */
#define M30_OK                        0
#define M30_ERR_INVAL                -1   /* 无效参数                       */
#define M30_ERR_NOMEM                -2   /* 内存分配失败                   */
#define M30_ERR_STATE                -3   /* 当前状态不允许此操作           */
#define M30_ERR_NO_DEVICE            -4   /* 未检测到 M30 设备              */
#define M30_ERR_MULTI_DEVICE         -5   /* 检测到多台 M30 设备            */
#define M30_ERR_SDK_INIT             -6   /* 厂商 SDK Init() 失败           */
#define M30_ERR_SDK_CALL             -7   /* 厂商 SDK 接口调用失败          */
#define M30_ERR_SERIAL               -8   /* 串口连接异常                   */
#define M30_ERR_CAMERA               -9   /* UVC 视频连接异常               */
#define M30_ERR_TIMEOUT             -10   /* 通信超时                       */
#define M30_ERR_IO                  -11   /* 文件/文件系统错误              */
#define M30_ERR_BUSY                -12   /* 操作冲突/资源被占用            */

/* ------------------------------------------------------------------------ */
/*  枚举类型                                                                 */
/* ------------------------------------------------------------------------ */

/* 摄像头类型 */
typedef enum {
    M30_CAM_RGB = 0,
    M30_CAM_IR  = 1,
} m30_cam_t;

/* 分辨率模式 */
typedef enum {
    M30_RES_720x1280 = 0,
    M30_RES_360x640  = 1,
    M30_RES_720x720  = 2,  /* M30/M20s only */
    M30_RES_720x640  = 3,  /* M30/M20s only */
} m30_resolution_t;

/* 删除底库模式 */
typedef enum {
    M30_DEL_ALL = 0,       /* 清空全部 */
    M30_DEL_BY_ID = 1,     /* 按ID删除 */
} m30_del_mode_t;

/* 识别模式 */
typedef enum {
    M30_REC_ONLY      = 0, /* 仅识别 */
    M30_REC_LIVENESS  = 1, /* 活体+识别 */
} m30_rec_mode_t;

/* 人脸模式 */
typedef enum {
    M30_FACE_SINGLE = 0,   /* 单人 */
    M30_FACE_MULTI  = 1,   /* 多人 */
} m30_face_mode_t;

/* 主动上报模式 */
typedef enum {
    M30_UPLOAD_ALL            = 0x00, /* 上报全部 */
    M30_UPLOAD_IMAGE_AND_RECO = 0x02, /* 图片+识别 (推荐) */
    M30_UPLOAD_FEAT_AND_RECO  = 0x03, /* 特征+识别 */
    M30_UPLOAD_RECO_ONLY      = 0x04, /* 仅识别 */
} m30_upload_mode_t;

/* 上报图片模式 */
typedef enum {
    M30_IMG_NONE              = 0x00,
    M30_IMG_RGB_FACE          = 0x01,
    M30_IMG_RGB_BG            = 0x02,
    M30_IMG_RGB_FACE_BG       = 0x03,
    M30_IMG_IR                = 0x04,
    M30_IMG_IR_RGB_FACE       = 0x05,
    M30_IMG_IR_RGB_BG         = 0x06,
    M30_IMG_ALL               = 0x07,
} m30_image_mode_t;

/* ------------------------------------------------------------------------ */
/*  数据类型                                                                 */
/* ------------------------------------------------------------------------ */

/* 不透明上下文句柄 */
typedef struct m30_ctx m30_ctx_t;

/* 原始帧描述符 */
typedef struct {
    uint8_t  *data;
    size_t    size;
    int       width;
    int       height;
    char      verify[2048]; /* SDK 返回的 json 识别数据 */
} m30_frame_t;

/* 创建选项 */
typedef struct {
    int log_level;          /* 0=TRACE .. 5=FATAL, 6=关闭 (默认2=INFO) */
    int log_target;         /* 0=控制台, 1=文件, 2=两者 (默认2) */
    int connect_timeout_ms; /* Ping 超时预算 (默认3000ms) */
} m30_config_t;

/* 回调函数类型 */
typedef void (*m30_report_cb)(char *data, int len);

/* ======================================================================== */
/*  生命周期管理                                                             */
/* ======================================================================== */

void        m30_default_config(m30_config_t *cfg);
m30_ctx_t  *m30_create(const m30_config_t *cfg);
void        m30_destroy(m30_ctx_t *ctx);
int         m30_open(m30_ctx_t *ctx);
int         m30_close(m30_ctx_t *ctx);
int         m30_is_open(const m30_ctx_t *ctx);
const char *m30_strerror(int err);
void        m30_shutdown_hook(m30_ctx_t *ctx);

/* ======================================================================== */
/*  设备信息查询                                                             */
/* ======================================================================== */

/* 链路连通性测试 */
int m30_ping(m30_ctx_t *ctx);
/* 查询系统版本号 */
int m30_get_version(m30_ctx_t *ctx, char *buf, size_t len);
/* 获取 SN 号, mode: 0=PCB SN, 1=Device SN */
int m30_get_sn(m30_ctx_t *ctx, int mode, char *buf, size_t len);
/* 获取设备型号 */
int m30_get_model(m30_ctx_t *ctx, char *buf, size_t len);
/* 查询 CPU 温度 */
int m30_get_cpu_temp(m30_ctx_t *ctx, unsigned int *temp_c);
/* 查询镜头 sensor 类型 */
int m30_get_sensor_model(m30_ctx_t *ctx, unsigned int *sensor);
/* 获取模组硬件版本号 */
int m30_get_hw_version(m30_ctx_t *ctx, char *buf, size_t len);
/* 获取/设置设备名称 */
int m30_get_device_name(m30_ctx_t *ctx, char *buf, size_t len);
int m30_set_device_name(m30_ctx_t *ctx, const char *name, size_t len);
/* 获取/设置 SDK 日志配置 */
int m30_get_log_config(m30_ctx_t *ctx, int *level, int *target);
int m30_set_log_config(m30_ctx_t *ctx, int level, int target);

/* ======================================================================== */
/*  视频流配置                                                               */
/* ======================================================================== */

/* 获取当前分辨率 */
int m30_get_resolution(m30_ctx_t *ctx, int *w, int *h);
/* 设置分辨率模式 (仅当前有效,重启无效) */
int m30_set_resolution(m30_ctx_t *ctx, m30_resolution_t mode);
/* 获取当前帧率 */
int m30_get_framerate(m30_ctx_t *ctx, unsigned int *fps);
/* 设置帧率, 范围10~25 (仅当前有效) */
int m30_set_framerate(m30_ctx_t *ctx, int fps);
/* 获取当前光敏值 */
int m30_get_light_sensitivity(m30_ctx_t *ctx, unsigned int *threshold);

/* ======================================================================== */
/*  摄像头开关控制                                                           */
/* ======================================================================== */

/* UVC 视频输出总开关, on: 1=开启 0=关闭 */
int m30_set_uvc_output(m30_ctx_t *ctx, int on);
/* 打开/关闭指定摄像头 */
int m30_set_camera_stream(m30_ctx_t *ctx, m30_cam_t cam, int on);
/* 查询摄像头开关状态 */
int m30_get_camera_stream(m30_ctx_t *ctx, m30_cam_t cam, int *is_open);
/* 切换 RGB/IR 视频流 (仅当前有效) */
int m30_switch_cam(m30_ctx_t *ctx, m30_cam_t cam);
/* 切换 RGB/IR 并设置镜像 (仅当前有效) */
int m30_mirror_cam(m30_ctx_t *ctx, m30_cam_t cam, int mirror);

/* ======================================================================== */
/*  抗闪烁 / IR 灯                                                          */
/* ======================================================================== */

/* 获取抗闪设置, cam_id: 0/1, hz输出: 0=50Hz 1=60Hz */
int m30_get_no_flicker(m30_ctx_t *ctx, int cam_id,
                       unsigned char *hz, unsigned char *enable);
/* 设置抗闪参数 (仅当前有效) */
int m30_set_no_flicker(m30_ctx_t *ctx, int cam_id, int hz, int enable);
/* 获取 IR 灯亮度和自动关闭时间 */
int m30_get_ir_light(m30_ctx_t *ctx, unsigned char *luminance,
                     unsigned char *close_time);
/* 设置 IR 灯, luminance: 0~200, close_time: 0~120秒 (仅当前有效) */
int m30_set_ir_light(m30_ctx_t *ctx, unsigned char luminance,
                     unsigned char close_time);

/* ======================================================================== */
/*  视频帧捕获                                                               */
/* ======================================================================== */

/* 拉取一帧 BGRA 数据，缓冲区由 ctx 内部管理，out->data 在下次调用前有效 */
int m30_get_frame(m30_ctx_t *ctx, m30_frame_t *out);
/* 抓取一帧并保存为 BMP */
int m30_save_frame_bmp(m30_ctx_t *ctx, const char *path);

/* ======================================================================== */
/*  AI 人脸底库管理                                                          */
/* ======================================================================== */

/* 模组抓拍入库 */
int m30_face_add(m30_ctx_t *ctx, const char *id, unsigned int id_len);
/* 上位机传入底图入库 (图片<100K, JPG/JPEG) */
int m30_face_add_by_image(m30_ctx_t *ctx, const char *id, unsigned int id_len,
                          const void *img, unsigned int img_len);
/* 模组抓拍入库并导出底图 (*out_img 需要 free()) */
int m30_face_add_return_image(m30_ctx_t *ctx, const char *id,
                              unsigned int id_len,
                              void **out_img, unsigned int *out_len);
/* 分片入库 (图片>100K, 每片<=8080字节) */
int m30_face_add_slice(m30_ctx_t *ctx, const char *id, unsigned int id_len,
                       unsigned int total_len, unsigned int pos,
                       int is_last, const void *slice, unsigned int slice_len);
/* 删除底库 */
int m30_face_delete(m30_ctx_t *ctx, m30_del_mode_t mode,
                    const char *id, unsigned int id_len);
/* 查询底库ID是否存在, 返回M30_OK=存在 */
int m30_face_query(m30_ctx_t *ctx, const char *id, unsigned int id_len);
/* 导出底库ID列表 */
int m30_face_get_id_list(m30_ctx_t *ctx, char *buf, unsigned int buf_len);
/* 获取底库数量 */
int m30_face_get_count(m30_ctx_t *ctx, unsigned int *count);

/* 用特征值添加底库 (特征长度固定1384) */
int m30_feature_add(m30_ctx_t *ctx, const char *id, unsigned int id_len,
                    const void *feat, unsigned int feat_len);
/* 用特征值更新底库 */
int m30_feature_update(m30_ctx_t *ctx, const char *id, unsigned int id_len,
                       const void *feat, unsigned int feat_len);
/* 查询底库特征值 */
int m30_feature_query(m30_ctx_t *ctx, const char *id, unsigned int id_len,
                      void *feat, unsigned int feat_len);

/* ======================================================================== */
/*  AI 人脸识别控制                                                          */
/* ======================================================================== */

/* 启动 1:N 识别 */
int m30_recognize_start_1n(m30_ctx_t *ctx, m30_rec_mode_t rec,
                           m30_face_mode_t face);
/* 启动 1:1 识别 (图片<300K) */
int m30_recognize_start_11(m30_ctx_t *ctx, m30_rec_mode_t rec,
                           m30_face_mode_t face,
                           const void *img, unsigned int img_len);
/* 启动 1:1 识别 (特征值) */
int m30_recognize_start_11_feature(m30_ctx_t *ctx, m30_rec_mode_t rec,
                                   m30_face_mode_t face,
                                   const void *feat, unsigned int feat_len);
/* 继续识别 */
int m30_recognize_resume(m30_ctx_t *ctx);
/* 暂停识别 */
int m30_recognize_pause(m30_ctx_t *ctx);
/* 查询识别状态, *running 输出 1=运行中 0=已暂停 */
int m30_recognize_query(m30_ctx_t *ctx, int *running);

/* 设置识别配置(json) */
int m30_set_rec_config(m30_ctx_t *ctx, const char *json, unsigned int len);
/* 获取识别配置(json) */
int m30_get_rec_config(m30_ctx_t *ctx, char *buf, unsigned int len);
/* 获取单次识别结果(json) */
int m30_get_single_recognize(m30_ctx_t *ctx, char *buf, unsigned int len);

/* 设置识别次数, 范围1~10 */
int m30_set_recognize_count(m30_ctx_t *ctx, unsigned char rec_count,
                            unsigned char living_count);
/* 获取识别次数 */
int m30_get_recognize_count(m30_ctx_t *ctx, unsigned char *rec_count,
                            unsigned char *living_count);

/* 设置模板更新 (需重启生效), 0=关闭 1=开启 */
int m30_set_template_update(m30_ctx_t *ctx, int enable);
/* 获取模板更新状态 */
int m30_get_template_update(m30_ctx_t *ctx, int *enabled);

/* 设置二维码识别 (仅当前有效), interval: 上报间隔秒(默认5) */
int m30_set_qrcode(m30_ctx_t *ctx, int enable, unsigned char interval);

/* 静态比对: 模组抓拍 (*result是json,需free()) */
int m30_static_compare(m30_ctx_t *ctx, void **result, unsigned int *result_len);
/* 静态比对: 上位机导入图片(<300K) */
int m30_static_compare_image(m30_ctx_t *ctx, const void *img,
                             unsigned int img_len,
                             void **result, unsigned int *result_len);

/* ======================================================================== */
/*  AI 数据上报                                                              */
/* ======================================================================== */

/* 开启帧内识别数据插入 */
int m30_open_frame_face_info(m30_ctx_t *ctx);
/* 关闭帧内识别数据插入 */
int m30_close_frame_face_info(m30_ctx_t *ctx);
/* 开启串口主动上报 */
int m30_open_ai_upload(m30_ctx_t *ctx, m30_upload_mode_t upload,
                       m30_image_mode_t image);
/* 关闭串口主动上报 */
int m30_close_ai_upload(m30_ctx_t *ctx);

/* 注册回调 */
int m30_register_reco_cb(m30_ctx_t *ctx, m30_report_cb cb);
int m30_register_track_cb(m30_ctx_t *ctx, m30_report_cb cb);
int m30_register_image_cb(m30_ctx_t *ctx, m30_report_cb cb);
int m30_register_feature_cb(m30_ctx_t *ctx, m30_report_cb cb);
int m30_register_qrcode_cb(m30_ctx_t *ctx, m30_report_cb cb);

/* ======================================================================== */
/*  系统维护                                                                 */
/* ======================================================================== */

/* 恢复出厂设置, keep_user_config: 1=保留配置 0=清空 */
int m30_recovery(m30_ctx_t *ctx, int keep_user_config);
/* 重启设备 */
int m30_reset(m30_ctx_t *ctx);
/* 固件升级: 分片上传 */
int m30_upload_firmware_slice(m30_ctx_t *ctx, unsigned int pos,
                              const void *data, unsigned int len);
/* 固件升级: 应用 (传入md5 hex小写) */
int m30_apply_upgrade(m30_ctx_t *ctx, const char *md5, unsigned int md5_len);

#ifdef __cplusplus
}
#endif

#endif /* UVC_M30_H */

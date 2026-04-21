# M30 UVC 应用层封装（基础框架）

面向嵌入式 Linux（ARM / ARM64），对 SenseTime M30 AI 模组的
`libAICameraModule.so` 进行纯 C 封装。

## 目录结构

```
m30_app/
├── include/
│   └── uvc_m30.h        # 对外公开 API（纯 C 接口）
├── src/
│   ├── uvc_m30.c        # 核心实现（线程安全 / 分阶段回滚）
│   ├── m30_sdk.h        # 纯 C 重新声明 libAICameraModule 符号
│   ├── uvc_log.{h,c}    # 分级日志
│   └── uvc_bmp.{h,c}    # BMP 写出工具
├── example/
│   └── main.c           # 交互式测试程序
├── Makefile
└── README.md
```

## 当前框架覆盖

| 分类 | 函数 |
|------|------|
| 生命周期 | `uvc_create / destroy / open / close / is_open / shutdown_hook` |
| 错误处理 | `uvc_strerror` |
| 设备信息 | `uvc_ping / get_version / get_sn / get_model / get_cpu_temp` |
| 流查询 | `uvc_get_resolution / get_framerate` |
| 开关控制 | `uvc_set_uvc_switch / camera_stream / get_camera_stream` |
| 帧捕获 | `uvc_get_frame / save_frame_bmp` |

## 工程质量

- `uvc_open()` 分阶段提交 + 完整回滚：枚举 → Init → 串口 → 摄像头 → Ping，任一阶段失败反向释放
- 每上下文递归互斥锁，所有公开函数线程安全
- SDK 语义反转已在封装层统一处理（SetUvcSwitch / SetCameraStream）
- 统一 `UVC_ERR_*` 错误码体系

## 编译

```bash
# 本地（x86_64 语法检查）
make TARGET_ARCH=linux64_14

# 交叉编译（ARM64）
make CROSS_COMPILE=aarch64-linux-gnu- TARGET_ARCH=aarch64_cmitech
```

## 测试菜单

```
0) Ping 探活
1) 设备信息 (版本/SN/型号/温度)
2) 查询分辨率/帧率
3) 保存单帧 BMP
4) 连续拉流 (Ctrl+C 停止)
5) UVC 输出开关
6) 摄像头开关 (RGB/IR)
7) 查询摄像头状态
```

## 后续扩展方向

- 人脸库管理（注册 / 删除 / 查询）
- 1:N / 1:1 人脸识别
- 异步事件回调（识别结果 / 追踪 / 图像上报）
- IR 补光灯 / 光感控制
- 视频流格式 / 分辨率 / 帧率设置

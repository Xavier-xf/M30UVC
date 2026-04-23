# CLAUDE.md


具体的API查看SenseEngine AI柬얾친莉Win&Linux역랙쌈왯賈痰匡도.md文档，没有的应该就是没有，对应功能也要仔细看，现在是框架差不多，就按照现在的框架，但是相应的API的注释要有，可以简要，然后函数名可以用M30不然分不清是什么UVC，注释是中文，打印信息是英语，根据这些要求完善一下当前框架添加其他的api，最好是有一个在ubuntu下的老化测试脚本，要挂机进行老化测试。
[2026-04-23 08:41:30] ========== Round 36 start ==========
[2026-04-23 08:41:30]   connect: OK
[2026-04-23 08:41:30]   ping: OK
[2026-04-23 08:41:30]   cpu temp: 49 C
[2026-04-23 08:41:30]   resolution: 720x1280  framerate: 25 fps
[2026-04-23 08:41:30]   version: platform_version=ViperNano-V2.2.0-pass-rv1109-sense-20250623195321  SN: M300AS11HC25M00240
[2026-04-23 08:41:30]   camera: RGB: on | IR: on
[2026-04-23 08:41:30]   frame save: OK -> frame_round36_084130.bmp (3686454 bytes)
[2026-04-23 08:41:30]   face db count: 1
[2026-04-23 08:41:30]   recognition: running
[2026-04-23 08:41:32]   stream test: 30s ...
[2026-04-23 08:42:02]   stream:  frames, avg  fps, min 0, max 0, err 
[2026-04-23 08:42:02]   stream test: FAILED (0 frames)
[2026-04-23 08:42:02]   WARN: stream test failed this round
^C[2026-04-23 08:42:03] === Aging test interrupted ===
[2026-04-23 08:42:03] ================================================================
[2026-04-23 08:42:03]   Rounds        : 36
[2026-04-23 08:42:03]   Pass / Fail   : 36 / 0
[2026-04-23 08:42:03]   Total frames  : 738
[2026-04-23 08:42:03]   Total errors  : 0
[2026-04-23 08:42:03]   FPS range     : 9999 ~ 0
[2026-04-23 08:42:03]   FPS warnings  : 0 (below 10 fps)
[2026-04-23 08:42:03]   Stream fails  : 35
[2026-04-23 08:42:03]   BMP fails     : 0
[2026-04-23 08:42:03]   Reconnects    : 0
[2026-04-23 08:42:03]   Max CPU temp  : 49 C
[2026-04-23 08:42:03] ================================================================
在当前测试脚本中，经常会[2026-04-23 08:42:02]   stream:  frames, avg  fps, min 0, max 0, err 
[2026-04-23 08:42:02]   stream test: FAILED (0 frames)，但是视频播放和保存也都是正常的，说明功能没问题，是不是脚本出问题了。
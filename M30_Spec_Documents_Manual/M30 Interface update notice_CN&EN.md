# M30差异性说明

因M30相比M20在硬件上存在升级和修改，为降低迁移成本，如无特别说明，相同接口和返回值均向前兼容M20；弃用接口或不支持的配置，仍可正常输入，但不发挥作用。

| 接口名称   | 差异概述 | 兼容性说明     |
| :---------- | ------------ | ------------ |
| GetLuminousSensitivityThreshold()  | M30采用RGB sensor来感光，当环境感光值低于18时，推荐打开上位机补光灯         |  兼容M20/M20S    |
| SetResolution() | M30相比M20支持更多预览分辨率格式         | 兼容M20/M20S |
| UpdateFeature() | M30新增接口，用于特征更新         | M20/M20S无此接口 |
| SetTemplateUpdate() | M30已废弃该接口，可调用但不生效 | M20不支持该接口；M20S支持该接口，但不推荐启用 |
| GetTemplateUpdate() | M30已废弃该接口，可调用但不生效 | M20不支持该接口；M20S支持该接口，但不推荐启用 |
| SetDeviceName()  | M30新增接口，用于自定义设备名称         | M20/M20S无此接口 |
| GetDeviceName()  | M30新增接口，用于读取自定义设备名称         | M20/M20S无此接口 |
| SetQRCodeSwitch() | M30不支持二维码识别         | M20不支持该接口；M20S支持该接口  |
| RegisterQRCodeReportCb() | M30不支持二维码识别         | M20不支持该接口；M20S支持该接口  |
| SetRecConfig jsonData | 1，M30 face_mode不再支持多人检测模式；max_face_cnt默认值为1； ae_mode仅支持模组自带ae；<br/>2，新增配置参数track_fps默认25fps，调低可降低算法资源占用，最低不建议低于8fps.<br/>3, 新增配置参数temper_strategy，当设备温度达到设定阈值时，将启动CPU降频策略。<br/>        | 如未配置参数，则为默认值 |
| AddFace() | 新增部分AI相关错误码         | 兼容M20/M20S |
| AddFaceWithQuality() | 新增部分AI相关错误码         | 兼容M20/M20S |
| AddFaceByImage() |  新增部分AI相关错误码         | 兼容M20/M20S |
| AddFaceByImageWithQuality() |  新增部分AI相关错误码         | 兼容M20/M20S |
| AddFaceReturnImage() |        新增部分AI相关错误码         | 兼容M20/M20S |
| AddFaceReturnImageWithQuality() |        新增部分AI相关错误码         | 兼容M20/M20S |
| AddFaceSlice() |         新增部分AI相关错误码         | 兼容M20/M20S |
| AddFaceSliceWithQuality() |       新增部分AI相关错误码         | 兼容M20/M20S |

# M30 Interfaces Notice:

Because M30 has hardware upgrades and modifications compared to M20, to reduce migration costs, where no special instructions are given, interfaces and return values are forward-compatible with M20. Deprecated interfaces and unsupported configurations can still be used, but will not function.

| Interface   | Remarks | Compatible Notice     |
| :---------- | ------------ | ------------ |
| GetLuminousSensitivityThreshold()  | M30 uses an RGB sensor to sense light, and when the environmental light value is less than 18, it is recommended to turn on the host computer's auxiliary lighting.         |  compatible with M20/M20S    |
| SetResolution() | M30 support more preview resolution than M20         | compatible with M20/M20S |
| UpdateFeature() | M30 new interface for feature updating         | M20/M20S doesn't support |
| SetTemplateUpdate() | M30 Deprecated interfaces | M20 doesn't support；M20S supports but not recommended |
| GetTemplateUpdate() | M30 Deprecated interfaces | M20 doesn't support；M20S supports but not recommended |
| SetDeviceName()  | M30 new interface for setting customized device name        | M20/M20S doesn't support |
| GetDeviceName()  | M30 new interface for getting customized device name         | M20/M20S doesn't support |
| SetQRCodeSwitch() | M30 doesn't support QR code         | M20 doesn't support；M20S supports  |
| RegisterQRCodeReportCb() | M30 doesn't support QR code         | M20 doesn't support；M20S supports  |
| SetRecConfig jsonData | 1，M30 no longer supports multi-person detection mode; the default value for max_facen_cnt is 1; ae_mode only supports the default mode of the module.<br/>2，new AI config settings: track_fps default value is 25fps，lowering it can reduce algorithm resource consumption, but not lower than 8fps is recommended.<br/>3, new AI config settings: temper_strategy, to low down CPU frequency when reaching high temperature protection degrees. <br/>        | If no parameters are configured, the default value will be used. |
| AddFace() | New error codes related to AI have been added.         | compatible with M20/M20S |
| AddFaceWithQuality() | New error codes related to AI have been added.         | compatible with M20/M20S |
| AddFaceByImage() | New error codes related to AI have been added.         | compatible with M20/M20S |
| AddFaceByImageWithQuality() | New error codes related to AI have been added.         | compatible with M20/M20S |
| AddFaceReturnImage() | New error codes related to AI have been added.         | compatible with M20/M20S |
| AddFaceReturnImageWithQuality() | New error codes related to AI have been added.         | compatible with M20/M20S |
| AddFaceSlice() | New error codes related to AI have been added.         | compatible with M20/M20S |
| AddFaceSliceWithQuality() | New error codes related to AI have been added.         | compatible with M20/M20S |
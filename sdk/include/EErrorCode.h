///
/// @file EErrorCode.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2024, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

namespace Crp {

enum EErrorCode {
  // common
  EC_OK                = 0x00,  ///< 成功
  EC_NetworkError      = 0x01,  ///< 网络问题
  EC_InvalidParameter  = 0x02,  ///< 参数错误
  EC_OutOfRange        = 0x03,  ///< 越界
  EC_InvalidLicense    = 0x04,  ///< License不合法
  EC_RobotInMoving     = 0x05,  ///< 机器人正在移动
  EC_NotSupportMethod  = 0x06,  ///< 不支持的接口
  EC_NotSupportFeature = 0x07,  ///< 不支持的功能
  EC_NotEnoughSpace    = 0x08,  ///< 空间不足，传入参数空间过小
  EC_TypeConversion    = 0x09,  ///< 类型转换失败
  EC_NotServoOn        = 0x0a,  ///< 未上使能
  EC_WrongWorkMode     = 0x0b,  ///< 工作模式不正确, 即钥匙档位Teach/Play/Remote

  // MotionService
  EC_MotionUninit = 0x20,
  EC_BufEmpty     = 0x21,
  EC_IsRunning    = 0x22,

  // ModelService
  EC_InvalidModel           = 0x70,  ///< Model参数不合法
  EC_CannotResolve_146      = 0x71,  ///< 1, 4, 6角度无法确定
  EC_NoSolution             = 0x72,  ///< 无解
  EC_CannotFindNearestAngle = 0x73,  ///< 找不到与cfg相近的角度
  EC_CouplingNegativeLimit  = 0x74,  ///< 耦合负限位
  EC_CouplingPositiveLimit  = 0x75,  ///< 耦合正限位
  EC_InvalidDHParam         = 0x76,  ///< DH参数错误
};
}  // namespace Crp

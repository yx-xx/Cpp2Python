///
/// @file IParamService.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2024, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

#include "IService.h"

namespace Crp {

/// 机器人参数枚举值
enum ERobotParam {
  /// 负软件限位
  RP_SoftwareLimitMin = 1,
  /// 正软件限位
  RP_SoftwareLimitMax = 2,
  /// 手动关节最大速度
  RP_MaxManualJointSpeed = 3,
  /// 自动关节最大速度
  RP_MaxAutoJointSpeed = 4,
  /// 手动关节加速度
  RP_MaxManualJointAcc = 5,
  /// 自动关节加速度
  RP_MaxAutoJointAcc = 6,
};

/// IParamService接口ID
#define ID_PARAM_SERVICE "D74D006E-2C3F-44A4-BB0E-0EF56605B6E7"

/// <summary>
/// 参数接口服务
/// </summary>
class IParamService : public IService {
public:
  virtual ~IParamService() = default;

  /// <summary>
  /// 获取关节参数值
  /// </summary>
  /// <param name="jointIndex">范围[0-11]</param>
  /// <param name="param">参数值枚举</param>
  /// <param name="value">参数值</param>
  /// <returns>成功返回true, 失败返回false</returns>
  virtual bool getBodyParam(size_t jointIndex, ERobotParam param, double& value) = 0;

  /// <summary>
  /// 设置关节参数值
  /// </summary>
  /// <param name="jointIndex">范围[0-11]</param>
  /// <param name="param">参数值枚举</param>
  /// <param name="value">要设置的参数值</param>
  /// <returns>成功返回true, 失败返回false</returns>
  virtual bool setBodyParam(size_t jointIndex, ERobotParam param, double const& value) = 0;
};
}  // namespace Crp

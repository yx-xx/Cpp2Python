///
/// @file IService.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2024, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

#include "RobotTypes.h"

namespace Crp {

/// <summary>
/// 所有接口服务的基类
/// </summary>
class IService {
public:
  virtual ~IService() = default;

  /// <summary>
  /// 服务ID,
  /// </summary>
  /// <returns>
  /// 返回服务的唯一ID
  /// </returns>
  virtual const char* serviceId() = 0;

  /// <summary>
  /// 服务名
  /// </summary>
  /// <returns>
  /// 返回服务名
  /// </returns>
  virtual const char* serviceName() = 0;

  /// <summary>
  /// 服务版本x.y.z
  /// </summary>
  /// <returns>
  /// 返回服务版本, 以x.y.z的格式
  /// </returns>
  virtual const char* serviceVersion() = 0;
};
}  // namespace Crp

///
/// @file IModelService.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2025, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

#include "IService.h"
#include "RobotTypes.h"

namespace Crp {

/// IModelService接口ID
#define ID_MODEL_SERVICE "CA3296D5-A0D6-4E0A-805F-3EC2056A0B49"

///@brief 机器人模型类型
enum class ERobotModel {
  Axis6,  ///< 工业6轴机器人
  Cobot,  ///< 协作6轴机器人
};

/// @brief 错误码
enum EErrorCode {
  EC_OK                     = 0x00,  ///< 成功
  EC_InvalidModel           = 0x70,  ///< Model参数不合法
  EC_CannotResolve_146      = 0x71,  ///< 1, 4, 6角度无法确定
  EC_NoSolution             = 0x72,  ///< 无解
  EC_CannotFindNearestAngle = 0x73,  ///< 找不到与cfg相近的角度
  EC_CouplingNegativeLimit  = 0x74,  ///< 耦合负限位
  EC_CouplingPositiveLimit  = 0x75,  ///< 耦合正限位
  EC_InvalidDHParam         = 0x76,  ///< DH参数错误
};

/// @brief 机器人模型服务
class IModelService : public IService {
public:
  virtual ~IModelService() = default;

public:
  /// @brief 正解
  /// @param[in] model 机器人建模类型
  /// @param[in] dh 标准DH参数, @see SStdDhParam
  /// @param[in] joints 关节角度 [j1 ... j6] @see SJointPosition
  /// @param[out] posture [x,y,z,Rx, Ry, Rz]目标位置和cfg @see SRobotPosition
  /// @return result @see EErrorCode
  virtual int32_t FKine(
      ERobotModel           model,
      SStdDHParam const&    dh,
      SJointPosition const& joints,
      SRobotPosition&       posture) = 0;

  /// @brief 反解
  /// @param[in] model 机器人建模类型
  /// @param[in] dh 标准DH参数, [a1 ... a7, d1 ... d7] @see SStdDHParam
  /// @param[in] posture 目标位置, 给定[x,y,z,Rx,Ry,Rz]和cfg
  /// @param[out] joints 反解结果关节值(角度)
  /// @return result @see EErrorCode
  virtual int32_t IKine(
      ERobotModel           model,
      SStdDHParam const&    dh,
      SRobotPosition const& posture,
      SJointPosition&       joints) = 0;

  /// @brief MoveL,MoveC就近反解, 在无法确定CFG配置，也无法确定1,4,6时, 使用离当前关节最近的解
  /// @param[in] model 机器人建模类型
  /// @param[in] dh 标准DH参数
  /// @param[in] src_joints 参考关节值(角度)和参考位置的cfg
  /// @param[in] dst_posture 目标位置[x, y, z, rx, ry, rz]
  /// @param[out] dst_joints 反解结果关节值(角度)和cfg
  /// @return result @see EErrorCode
  virtual int32_t IKine_nearest_line(
      ERobotModel           model,
      SStdDHParam const&    dh,
      SJointPosition const& src_joints,
      SRobotPosition const& dst_posture,
      SJointPosition&       dst_joints) = 0;

  /// @brief MoveJ就近反解, 在无法确定CFG配置，也无法确定1,4,6时, 使用离当前关节最近的解
  /// @param[in] model 机器人建模类型
  /// @param[in] dh 标准DH参数, [a1 ... a7, d1 ... d7]
  /// @param[in] src_joints 参考关节值(角度)
  /// @param[in] dst_posture 目标位置[x, y, z, rx, ry, rz]
  /// @param[out] dst_joints 反解结果关节值(角度)和cfg
  /// @return result @see EErrorCode
  virtual int32_t IKine_nearest_joint(
      ERobotModel           model,
      SStdDHParam const&    dh,
      SJointPosition const& src_joints,
      SRobotPosition const& dst_posture,
      SJointPosition&       dst_joints) = 0;

  /// @brief 根据joint的关节值计算cfg
  /// @param[in] model 机器人建模类型
  /// @param[in] dh 标准dh参数 @see SStdDHParam
  /// @param[in,out] joints 输入关节角度(角度)，输出cfg值 @see SJointPosition
  /// @return result @see EErrorCode
  virtual int32_t calcCfg(
      ERobotModel        model,
      SStdDHParam const& dh,
      SJointPosition&    joints) = 0;
};
}  // namespace Crp

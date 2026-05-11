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
  /// @return result
  /// @attention 离线计算，无工具、用户、外部轴等信息, 使用 @see joint2position
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
  /// @attention 离线计算，无工具、用户、外部轴等信息, 使用 @see position2joint
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
  /// @attention 不改变构型的就近解， 即cfgx不变化
  /// @attention 离线计算，无工具、用户、外部轴等信息, 使用 @see position2joint
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
  /// @attention 会改变构型的就近解, 即cfgx值可变
  /// @attention 离线计算，无工具、用户、外部轴等信息, 使用 @see position2joint
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
  /// @attention 离线计算，无工具、用户、外部轴等信息, 使用 @see position2joint
  virtual int32_t calcCfg(
      ERobotModel        model,
      SStdDHParam const& dh,
      SJointPosition&    joints) = 0;

  /// @brief 关节坐标转笛卡尔坐标
  /// @param[in] srcJoint 关节角度
  /// @param[in] srcJointCount 关节角度数量
  /// @param[in] dstToolNum dstPos的工具号
  /// @param[in] dstUserNum dstPos的用户号
  /// @param[in] dstRefCoord dstPos的参考坐标系，见<see cref="int"/>
  /// @param[out] dstPos 转换后的坐标系
  /// @param[in] dstPosCount 转换后的坐标系数量
  /// @return 错误码, 见<see cref="EErrorCode"/>
  /// - EC_OK                = 0x00
  /// - EC_NetworkError      = 0x01
  /// - EC_InvalidParameter  = 0x02
  /// - EC_OutOfRange        = 0x03
  /// - EC_NotSupportMethod  = 0x06
  /// @attention 此函数要求CrobotpOS 1.14.7及以上
  /// @since 1.2.0
  virtual int32_t joint2Position(
      SJointPosition const* srcJoint,
      size_t                srcJointCount,
      SRobotPosition*       dstPos,
      size_t                dstPosCount,
      int32_t               dstToolNum,
      int32_t               dstUserNum,
      int32_t               dstRefCoord) = 0;

  /// @brief 关节坐标转笛卡尔坐标
  /// @since 1.2.0
  inline int32_t joint2Position(
      SJointPosition const& srcJoint,
      SRobotPosition*       dstPos,
      int32_t               dstToolNum,
      int32_t               dstUserNum,
      int32_t               dstRefCoord) {
    return joint2Position(&srcJoint, 1u, dstPos, 1u, dstToolNum, dstUserNum, dstRefCoord);
  }

  /// @brief 笛卡尔坐标转关节坐标
  /// @param[in] srcPos 笛卡尔坐标
  /// @param[in] srcPosCount 笛卡尔坐标的输入数量
  /// @param[in] srcToolNum srcPos的工具号
  /// @param[in] srcUserNum srcPos的用户号
  /// @param[in] srcRefCoord srcPos的参考坐标系，见<see cref="int"/>
  /// @param[out] dstJoint 转换后的关节角度
  /// @param[in] dstJointCount 转换后的关节角度数量，与srcPosCount相同
  /// @return 错误码, 见<see cref="EErrorCode"/>
  /// - EC_OK                = 0x00
  /// - EC_NetworkError      = 0x01
  /// - EC_InvalidParameter  = 0x02
  /// - EC_OutOfRange        = 0x03
  /// - EC_NotSupportMethod  = 0x06
  /// @attention 此函数要求CrobotpOS 1.14.7及以上
  /// @since 1.2.0
  virtual int32_t position2Joint(
      SRobotPosition const* srcPos,
      size_t                srcPosCount,
      int32_t               srcToolNum,
      int32_t               srcUserNum,
      int32_t               srcRefCoord,
      SJointPosition*       dstJoint,
      size_t                dstJointCount) = 0;

  /// @brief 笛卡尔坐标转关节坐标
  /// @since 1.2.0
  inline int32_t position2Joint(
      SRobotPosition const& srcPos,
      int32_t               srcToolNum,
      int32_t               srcUserNum,
      int32_t               srcRefCoord,
      SJointPosition*       dstJoint) {
    return position2Joint(&srcPos, 1u, srcToolNum, srcUserNum, srcRefCoord, dstJoint, 1u);
  }

  /// @brief 笛卡尔坐标系之间的转换
  /// @param[in] srcPos 要转换的笛卡尔坐标点
  /// @param[in] srcPosCount srcPos的数量
  /// @param[in] srcToolNum srcPos的工具号
  /// @param[in] srcUserNum srcPos的用户号
  /// @param[in] srcRefCoord srcPos的参考坐标系，见<see cref="int"/>
  /// @param[in] dstToolNum dstPos的工具号
  /// @param[in] dstUserNum dstPos的用户号
  /// @param[in] dstRefCoord dstPos参考的坐标系，见<see cref="int"/>
  /// @param[out] dstPos 转换后的笛卡坐标
  /// @param[in] dstPosCount dstPos的数量, 与srcPosCount的数量相同
  /// @return 错误码, 见<see cref="EErrorCode"/>
  /// - EC_OK                = 0x00
  /// - EC_NetworkError      = 0x01
  /// - EC_InvalidParameter  = 0x02
  /// - EC_OutOfRange        = 0x03
  /// - EC_NotSupportMethod  = 0x06
  /// @attention 此函数要求CrobotpOS 1.14.7及以上
  /// @since 1.3.0
  virtual int32_t convertCoordSys(
      SRobotPosition const* srcPos,
      size_t                srcPosCount,
      int32_t               srcToolNum,
      int32_t               srcUserNum,
      int32_t               srcRefCoord,
      SRobotPosition*       dstPos,
      size_t                dstPosCount,
      int32_t               dstToolNum,
      int32_t               dstUserNum,
      int32_t               dstRefCoord) = 0;

  /// @brief 笛卡尔坐标系之间的转换
  /// @since 1.3.0
  inline int32_t convertCoordSys(
      SRobotPosition const& srcPos,
      int32_t               srcToolNum,
      int32_t               srcUserNum,
      int32_t               srcRefCoord,
      SRobotPosition*       dstPos,
      int32_t               dstToolNum,
      int32_t               dstUserNum,
      int32_t               dstRefCoord) {
    return convertCoordSys(
        &srcPos, 1u, srcToolNum, srcUserNum, srcRefCoord,
        dstPos, 1u, dstToolNum, dstUserNum, dstRefCoord);
  }

  /// @brief 笛卡尔坐标转关节坐标, 以当前位置为参考点计算笛卡尔位置的cfg
  /// @param[in,out] pos 笛卡尔坐标, 输入位姿，cfg不使用, 输出cfg, 输出的cfx与当前点位一致
  /// @param[in] posCount pos的数量
  /// @param[in] posToolNum pos的工具号
  /// @param[in] posUserNum pos的用户号
  /// @param[in] posRefCoord pos的参考坐标系，见<see cref="ECoordinateSystem"/>
  /// @return 错误码, 见<see cref="EErrorCode"/>
  /// - EC_OK                = 0x00
  /// - EC_NetworkError      = 0x01
  /// - EC_InvalidParameter  = 0x02
  /// - EC_OutOfRange        = 0x03
  /// - EC_NotSupportMethod  = 0x06
  /// - 反解错误              = -1, 可能原因: 点位不可达, 奇异点附近
  /// @attention 此函数要求CrobotpOS 1.14.7及以上
  /// @since 1.3.0
  virtual int32_t calcCfg(
      SRobotPosition* pos,
      size_t          posCount,
      int32_t         posToolNum,
      int32_t         posUserNum,
      int32_t         posRefCoord) = 0;

  /// @brief 以当前位置为参考点计算笛卡尔位置的cfg
  /// @since 1.3.0
  inline int32_t calcCfg(
      SRobotPosition* pos,
      int32_t         toolNum,
      int32_t         userNum,
      int32_t         refCoord) {
    return calcCfg(pos, 1u, toolNum, userNum, refCoord);
  }

  /// 根据指定参考点计算笛卡尔坐标cfg
  /// @param[in,out] pos 笛卡尔坐标, 输入位姿，cfg不使用, 输出cfg, 输出的cfx与当前点位一致
  /// @param[in] posCount pos的数量
  /// @param[in] posToolNum pos的工具号
  /// @param[in] posUserNum pos的用户号
  /// @param[in] posRefCoord pos的参考坐标系，见<see cref="ECoordinateSystem"/>
  /// @param[in] refPos 参考坐标位置，此位置的CFG，必须正确，否则计算结果不正确
  /// @param[in] refPosCount refPos的数量，应该与posCount一致
  /// @param[in] refPosToolNum refPos的工具号
  /// @param[in] refPosUserNum refPos的用户号
  /// @param[in] refPosRefCoord refPos的参考坐标系，见<see cref="ECoordinateSystem"/>
  /// @return 错误码, 见<see cref="EErrorCode"/>
  /// - EC_OK                = 0x00
  /// - EC_NetworkError      = 0x01
  /// - EC_InvalidParameter  = 0x02
  /// - EC_OutOfRange        = 0x03
  /// - EC_NotSupportMethod  = 0x06
  /// - 反解错误              = -1, 可能原因: 点位不可达, 奇异点附近
  /// @attention 此函数要求CrobotpOS 1.14.7及以上
  /// @since 1.3.0
  virtual int32_t calcCfgFromPos(
      SRobotPosition*       pos,
      size_t                posCount,
      int32_t               posToolNum,
      int32_t               posUserNum,
      int32_t               posRefCoord,
      SRobotPosition const* refPos,
      size_t                refPosCount,
      int32_t               refPosToolNum,
      int32_t               refPosUserNum,
      int32_t               refPosRefCoord) = 0;

  /// @brief 根据指定参考点计算笛卡尔坐标cfg
  /// @since 1.3.0
  inline int32_t calcCfgFromPos(
      SRobotPosition*       pos,
      int32_t               posToolNum,
      int32_t               posUserNum,
      int32_t               posRefCoord,
      SRobotPosition const* refPos,
      int32_t               refPosToolNum,
      int32_t               refPosUserNum,
      int32_t               refPosRefCoord) {
    return calcCfgFromPos(
        pos, 1u, posToolNum, posUserNum, posRefCoord,
        refPos, 1u, refPosToolNum, refPosUserNum, refPosRefCoord);
  }

  /// @brief 根据参考关节计算笛卡尔坐标的cfg
  /// @param[in,out] pos 笛卡尔坐标, 输入位姿，cfg不使用, 输出cfg, 输出的cfx与当前点位一致
  /// @param[in] posCount pos的数量
  /// @param[in] posToolNum pos的工具号
  /// @param[in] posUserNum pos的用户号
  /// @param[in] posRefCoord pos的参考坐标系，见<see cref="ECoordinateSystem"/>
  /// @param[in] refJoints 参考关节，不使用cfg
  /// @param[in] refJointsCount refJoints的数量，值应与posCount一致
  /// @return 错误码, 见<see cref="EErrorCode"/>
  /// - EC_OK                = 0x00
  /// - EC_NetworkError      = 0x01
  /// - EC_InvalidParameter  = 0x02
  /// - EC_OutOfRange        = 0x03
  /// - EC_NotSupportMethod  = 0x06
  /// - 反解错误              = -1, 可能原因: 点位不可达, 奇异点附近
  /// @attention 此函数要求CrobotpOS 1.14.7及以上
  /// @since 1.3.0
  virtual int32_t calcCfgFromJoint(
      SRobotPosition*       pos,
      size_t                posCount,
      int                   posToolNum,
      int                   posUserNum,
      int                   posRefCoord,
      SJointPosition const* refJoints,
      size_t                refJointsCount) = 0;

  /// @brief 根据参考关节计算笛卡尔坐标的cfg
  /// @since 1.3.0
  inline int32_t calcCfgFromJoint(
      SRobotPosition*       pos,
      int                   posToolNum,
      int                   posUserNum,
      int                   posRefCoord,
      SJointPosition const* refJoints) {
    return calcCfgFromJoint(pos, 1u, posToolNum, posUserNum, posRefCoord, refJoints, 1u);
  }
};
}  // namespace Crp

///
/// @file RobotTypes.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2024, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

#include <stdint.h>
#include <cstddef>

namespace Crp {

/// <summary>
/// 机器人位置数据
/// </summary>
struct SRobotPosition {
  /// X坐标
  double x;
  /// Y坐标
  double y;
  /// Z坐标
  double z;
  /// 绕X轴旋转角度
  double Rx;
  /// 绕Y轴旋转角度
  double Ry;
  /// 绕Z轴旋转角度
  double Rz;
  /// 外部轴坐标
  double extJoint[6];
  /// # 1. cf1, cf4, cf6:
  /// ## 1.1 旋转轴：
  /// 象限编号从0开始正向1、2、3等（负向 - 1、- 2、- 3等），以此类推。
  /// - 0表示从零角度开始，正向旋转第一个四分之一圈，即0°到90°；
  /// - 1表示正向旋转第二个四分之一圈，即90°到180°
  /// - 2表示正向旋转第二个四分之一圈，即180°到270°
  /// - 3表示正向旋转第二个四分之一圈，即270°到360°
  /// - -1表示负向旋转第一个四分之一圈，即0°到-90°；
  /// - -2表示负向旋转第二个四分之一圈，即-90°到-180°
  /// - -3表示负向旋转第二个四分之一圈，即-180°到-270°
  /// - -4表示负向旋转第二个四分之一圈，即-270°到-360°
  /// ## 1.2 直线轴
  /// 轴配置定义间隔米数。0表示介于0到1米之间的位置，1表示介于1到2米之间的位置，-1表示介于0到-1米之间的位置，以此类推
  /// # 2. cfx
  /// cfx | 腕部中心相对于1轴 | 腕部中心相对于下臂 | 5轴角度
  /// ----| -----------------| -----------------|--------
  ///   0 |       前面       |        前面       |    正
  ///   1 |       前面       |        前面       |    负
  ///   2 |       前面       |        后面       |    正
  ///   3 |       前面       |        后面       |    负
  ///   4 |       后面       |        前面       |    正
  ///   5 |       后面       |        前面       |    负
  ///   6 |       后面       |        后面       |    正
  ///   7 |       后面       |        后面       |    负
  /// - cfg[0] = cf1 关节1象限，
  /// - cfg[1] = cf4 关节4象限
  /// - cfg[2] = cf6 关节6象限
  /// - cfg[3] = cfx 描述机器人的形态，8种机器人配置一种, 值为负时，代表当前cfg无效，为计算点
  int cfg[4];
};

/// <summary>
/// 关节坐标系
/// </summary>
struct SJointPosition {
  /// 本体关节
  double body[6];
  /// 外部轴关节
  double ext[6];
  /// 见 <see cref="SRobotPosition" /> 中cfg, 读取机器人数据存储时使用，写入时无意义，全部给0即可
  int cfg[4];
};

/// <summary>
/// 欧拉角，用角度表示
/// </summary>
struct SRobotPosture {
  /// X
  double x;
  /// Y
  double y;
  /// Z
  double z;
  /// Rx
  double Rx;
  /// Ry
  double Ry;
  /// Rz
  double Rz;
};

/// <summary>
/// 标准DH参数
/// </summary>
struct SStdDHParam {
  double a1;
  double a2;
  double a3;
  double a4;
  double a5;
  double a6;
  double a7;

  double d1;
  double d2;
  double d3;
  double d4;
  double d5;
  double d6;
  double d7;
};

/// <summary>
/// 钥匙档位状态
/// </summary>
enum ERobotMode {
  /// 手动
  RM_Manual = 0,
  /// 自动
  RM_Playing = 1,
  /// 远程
  RM_Remote = 2,
};

/// <summary>
/// 机器人坐标系枚举值
/// </summary>
enum ECoordinateSystem {
  /// 关节坐标系
  CS_Joint = 0,
  /// 世界坐标系
  CS_World = 1,
  /// 基坐标系
  CS_Base = 2,
  /// 用户坐标系
  CS_User = 3,
  /// 工具坐标系
  CS_Tool = 4,
};

/// <summary>
/// 试运行模式
/// </summary>
enum EDryRunMode {
  /// 单行试运行
  DRY_SINGLE = 0,
  /// 连续试运行
  DRY_CONTINUOUS,
  /// 空试运行
  DRY_EMPTY,
};

/// <summary>
/// 自动运行模式
/// </summary>
enum EAutoRunMode {
  /// 单行
  AUTO_SINGLE_LINE = 0,
  /// 单次循环
  AUTO_SINGLE_LOOP,
  /// 连续循环
  AUTO_CONTINUOUS_LOOP,
};

/// <summary>
/// 程序运行状态
/// </summary>
enum EProgramStatus {
  /// 程序停止
  PS_Stop = 0,
  /// 程序运行
  PS_Running = 1,
  /// 程序暂停
  PS_Pause = 2,
};

/// <summary>
/// T, C变量
/// </summary>
struct STCVariable {
  /// 是否设定
  bool available;
  /// 保留
  bool reserved[3];
  /// 初始值
  int32_t initValue;
  /// 当前值
  int32_t currentValue;
};

/// <summary>
/// 用户号数据
/// </summary>
struct SUserData {
  /// 偏移
  SRobotPosture posture;
  /// 已标定？
  bool calibrated;
  /// 机器人握住工具？
  bool isHeld;
  /// 被机械单元移动
  bool isMovable;
  /// reserved;
  bool reserved;
};

/// <summary>
/// 工具号
/// </summary>
struct SToolData {
  /// 质量
  double weight;
  /// 重心X
  double centerX;
  /// 重心Y
  double centerY;
  /// 重心Z
  double centerZ;
  /// 惯性矩X
  double inertiaX;
  /// 惯性矩Y
  double inertiaY;
  /// 惯性矩Z
  double inertiaZ;
  /// X, Y, Z, Rx, Ry, Rz
  SRobotPosture offset;
  /// 已标定？
  bool calibrated;
  /// 机器人握住工具？
  bool isHeld;
  /// reserved
  bool reserved[2];
};

}  // namespace Crp

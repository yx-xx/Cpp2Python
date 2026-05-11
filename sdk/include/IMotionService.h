///
/// @file IMotionService.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2025, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

#include "IService.h"

namespace Crp {

#define ID_MOTION_SERVICE "971342ED-D6F3-4462-A198-1E2908E5D600"

/// <summary>
/// 引导类型
/// </summary>
enum class EMotionType {
  Path        = 0,  ///< 路径引导控制，关节数据或笛卡尔数据
  Instruction = 1,  ///< 指令引导控制
};

/// <summary>
/// movePath 返回值
/// </summary>
enum class EMovePathResult {
  Success    = 0,  ///< 启动成功， 开始移动
  NotInit    = 1,  ///< 未初始化
  BufEmpty   = 2,  ///< Buffer为空
  IsRunning  = 3,  ///< 正在运行
  ParamError = 4,  ///< 参数错误
};

/// <summary>
/// 直线/圆弧分量选择策略
/// </summary>
enum class EMoveStrategy {
  TimeFirst     = 0,  ///< 时间长优先
  DistanceFirst = 1,  ///< 位置优先
  PoseFirst     = 2,  ///< 姿态优先
};

/// <summary>
/// 运动指令相关参数
/// </summary>
struct SMotionParam {
  double  speed;         ///< 速度值, 关节运动时: 范围：[1, 100], 单位百分比; 笛卡尔运动时: 单位mm/s
  double  pl     = 0.0;  ///< 平滑等级: 范围 [0,9]
  int32_t smooth = 0;    ///< 滤波等级, 范围：[0, 9] 值越大, 滤波时间越短, 步长滤波模式生效
  int32_t acc    = 1;    ///< 加速度, 范围: [1, 20] 值越大, 加速度越小
  int32_t dec    = 1;    ///< 减速度, 范围: [1, 20] 值越大, 加速度越小
};

/// <summary>
/// MoveAbsJ指令参数
/// </summary>
struct SInstMoveAbsJ {
  SJointPosition joint;  ///< 目标关节位置
  SMotionParam   param;  ///< 运动参数
};

/// <summary>
/// MoveJ指令参数
/// </summary>
struct SInstMoveJ {
  SRobotPosition targetPos;  ///< 目标笛卡尔位置
  SMotionParam   param;      ///< 运动参数
};

/// <summary>
/// MoveL指令参数
/// </summary>
struct SInstMoveL {
  SRobotPosition targetPos;  /// 目标笛卡尔位置
  SMotionParam   param;      /// 运动参数
  EMoveStrategy  strategy;   /// 策略, 见<see cref="EMoveStrategy"/>
};

/// <summary>
/// MoveC指令参数
/// </summary>
struct SInstMoveC {
  SRobotPosition p2;        ///< 圆弧P2点，P1使用上一个运动的结束点
  SRobotPosition p3;        ///< 圆弧P3点
  SMotionParam   param;     ///< 运动参数
  EMoveStrategy  strategy;  ///< 策略, 见<see cref="EMoveStrategy"/>
};

/// <summary>
/// MoveJump指令参数
/// </summary>
struct SInstMoveJump {
  SRobotPosition targetPos;  ///< 目标笛卡尔位置
  SMotionParam   param;      ///< 运动参数
  EMoveStrategy  strategy;   ///< 策略, 见<see cref="EMoveStrategy"/>
  double         top;        ///< 门限高度
  double         up;         ///< 上升高度
  double         down;       ///< 下降高度
};

/// <summary>
/// 引导运动服务
/// > \attention
/// > - 请在充分理解并掌握此功能的情况下，才进行使用
/// > - 请在确保安全的情况下才使用此功能
/// </summary>
class IMotionService : public IService {
public:
  virtual ~IMotionService() = default;

  /// <summary>
  /// 在连接到控制器后，判断控制器是否支持MotionService
  /// </summary>
  /// <returns>
  /// - false: 未连接到控制器，或者不支持MotionService
  /// - true: 控制支持MotionService
  /// </returns>
  virtual bool isAvailable() = 0;

  /// <summary>
  /// 获取机器人的用户坐标反馈位置
  /// </summary>
  /// <param name="pos">返回机器人的坐标位置，其中cfg都为0</param>
  /// <param name="toolNo">工具号</param>
  /// <param name="userNo">用户号</param>
  /// <returns>
  /// - false: 失败，如果工具号、用户号设置不合理
  /// - true: 成功
  /// </returns>
  virtual bool currentUserPosition(SRobotPosition& pos, int32_t toolNo, int32_t userNo) = 0;

  /// <summary>
  /// 控制器是否准备好接收数据: 位置数据或指令数据
  /// 程序运行到GuidancePosRun或GuidanceInstRun
  /// </summary>
  /// <param name="type">引导类型</param>
  /// <returns>
  /// - 已就绪返回true
  /// - 未就绪返回false
  /// </returns>
  virtual bool isReady(EMotionType type) = 0;

  /// <summary>
  /// 位置引导最大可以使用的缓冲区
  /// </summary>
  /// <returns>返回最大可以使用的缓冲区</returns>
  virtual size_t getMaxPathBufferSize() = 0;

  /// <summary>
  /// 当前可以使用的缓冲区长度，数据被消费后，可用缓存区变大
  /// </summary>
  /// <returns>返回当前可以使用的缓冲区数量</returns>
  virtual size_t getAvailPathBufferSize() = 0;

  /// <summary>
  /// 按给定的关节位置流运动，需要不间断发送关节位置数据流，此时机器人本体完全按照外部发送的位置进行规划运动。
  /// </summary>
  /// <param name="jointsArray">关节位置数据，忽略CFG</param>
  /// <param name="jointCount">数组的长度</param>
  /// <returns></returns>
  /// > \attention 指令运行在GuidancePosRun时，才能调用成功
  /// > \attention
  /// > - 位置数据必须保持间隔时间必须保持一致，且间隔取值范围为2ms的1~50倍关系，如全部发送8ms的关节位置数据流
  /// > - 点位数据的间隔时间必须保持一致，不能2ms,4ms混在一起发送，例如：必须都为2ms的位置数据，或都为4ms的位置数据
  /// > \attention
  /// > - 发送关节流前，机器人的当前关节位置，必须在第1个关节发送的关节位置，否则可能引发飞车
  virtual bool sendPath(SJointPosition const jointsArray[], size_t jointCount) = 0;

  /// <summary>
  /// 按给定的关节位置流运动，需要不间断发送笛卡尔位置数据流，此时机器人本体完全按照外部发送的位置进行规划运动。
  /// 位置数据必须保持间隔时间不变，间隔取值范围为2ms的1~50倍关系，如全部发送8ms的笛卡尔位置数据流
  /// 可以连续多次调用
  /// </summary>
  /// <param name="posArray">笛卡尔位置流, 忽略CFG</param>
  /// <param name="posCount">数组长度</param>
  /// <param name="toolNo">工具号[0-50]</param>
  /// <param name="userNo">用户号[0-50]</param>
  /// <returns></returns>
  /// > \attention 指令运行在GuidancePosRun时，才能调用成功
  /// > \note
  /// > 位置发送必须在位置流消费完成发送
  /// > 位置可以分多次分段发送, 调用finalize()后不再接受新的位置流, 等待指令消费完成
  /// > \attention
  /// > - 位置数据必须保持间隔时间必须保持一致，且间隔取值范围为2ms的1~50倍关系，如全部发送8ms的关节位置数据流
  /// > - 点位数据的间隔时间必须保持一致，不能2ms,4ms混在一起发送，例如：必须都为2ms的位置数据，或都为4ms的位置数据
  /// > - 在movePath中指定2ms的插补倍率, 如movePath(4)，表示插补的周期是8ms
  /// > \attention
  /// > - 发送位置流前，机器人的当前位置，必须在第1个发送的位置，否则可能引发飞车
  virtual bool sendPath(SRobotPosition const posArray[], size_t posCount, int32_t toolNo, int32_t userNo) = 0;

  /// <summary>
  /// 按sendPath的轨迹开始移动, 开始move后，可以连接发送
  /// </summary>
  /// <param name="ratio">路径插补周期2ms的倍率，范围1-50</param>
  /// <returns>见 <see cref="EMovePathResult"/> </returns>
  /// \attention 机器人当前位置如果不在第一个点，机器人会首先以关节运动的方式，移动到第1个点，再以插补周期的数据进行移动
  /// \attention 指令运行在GuidancePosRun时，才能调用成功
  virtual EMovePathResult movePath(int32_t ratio) = 0;

  /// <summary>
  /// 关节运动
  /// </summary>
  /// <param name="index"></param>
  /// <param name="inst"></param>
  /// <returns>成功返回true, 失败返回false</returns>
  /// \attention 指令运行在GuidanceInstRun时，才能调用成功
  virtual bool moveAbsJ(int32_t index, SInstMoveAbsJ const& inst) = 0;

  /// <summary>
  /// 以关节运动的方式，运动到给定的笛卡尔位置
  /// </summary>
  /// <param name="index"></param>
  /// <param name="inst"></param>
  /// <returns>成功返回true, 失败返回false</returns>
  /// \attention 指令运行在GuidanceInstRun时，才能调用成功
  virtual bool moveJ(int32_t index, SInstMoveJ const& inst) = 0;

  /// <summary>
  /// 直线运动到笛卡尔位置
  /// </summary>
  /// <param name="index"></param>
  /// <param name="inst"></param>
  /// <returns>成功返回true, 失败返回false</returns>
  /// \attention 指令运行在GuidanceInstRun时，才能调用成功
  virtual bool moveL(int32_t index, SInstMoveL const& inst) = 0;

  /// <summary>
  /// 圆弧运动,
  /// </summary>
  /// <param name="index"></param>
  /// <param name="inst"></param>
  /// <returns>成功返回true, 失败返回false</returns>
  /// \attention 指令运行在GuidanceInstRun时，才能调用成功
  virtual bool moveC(int32_t index, SInstMoveC const& inst) = 0;

  /// <summary>
  /// 门型运动
  /// </summary>
  /// <param name="index"></param>
  /// <param name="inst"></param>
  /// <returns>成功返回true, 失败返回false</returns>
  /// \attention 指令运行在GuidanceInstRun时，才能调用成功
  virtual bool moveJump(int32_t index, SInstMoveJump const& inst) = 0;

  /// <summary>
  /// 当前指令的序号
  /// </summary>
  /// <returns>返回当前序号, -1表示错误
  /// </returns>
  virtual int32_t currentIndex() = 0;

  /// <summary>
  /// 结束发送运动轨迹,或运动指令, 机器人指令中当前行运行完成，并自动转到下一行执行
  /// </summary>
  /// <param name="type">见<see cref="EMotionType"/></param>
  /// <returns>成功返回true, 失败返回false</returns>
  /// \attention 调用必须在moveXXX接口之后才能生效
  virtual bool finalize(EMotionType type) = 0;
};

}  // namespace Crp

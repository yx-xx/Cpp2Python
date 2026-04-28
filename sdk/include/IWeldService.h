///
/// @file IWeldService.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2024, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

#include "IService.h"

namespace Crp {

/// IWeldService接口ID
#define ID_WELD_SERVICE "EDF312BE-2403-4109-8001-09FCF7EC2044"

/// <summary>
/// 焊接工艺参数
/// </summary>
struct SWeldingProcess {
  /// <summary>
  /// 焊接电流
  /// </summary>
  int32_t current;

  /// <summary>
  /// 焊接电压
  /// </summary>
  double voltage;

  /// <summary>
  /// 起弧电流
  /// </summary>
  int32_t arcCurrent;

  /// <summary>
  /// 起弧电压
  /// </summary>
  double arcVoltage;

  /// <summary>
  /// 起弧过渡时间
  /// </summary>
  int32_t arcTimeTransition_ms;

  /// <summary>
  /// 收弧电流
  /// </summary>
  int32_t arcOutCurrent;

  /// <summary>
  /// 收弧电压
  /// </summary>
  double arcOutVoltage;

  /// <summary>
  /// 弧坑时间
  /// </summary>
  int32_t arcOut_ms;

  /// <summary>
  /// 提前送气时间
  /// </summary>
  int32_t gasPreFlow_ms;

  /// <summary>
  /// 滞后送气时间
  /// </summary>
  int32_t gasPostFlow_ms;

  /// <summary>
  /// 焊完抽丝时间
  /// </summary>
  int32_t backWire_ms;

  /// <summary>
  /// 飞行起弧时间
  /// </summary>
  int32_t arcFly_ms;
};

typedef SWeldingProcess SWeldingProcessParam;

/// <summary>
/// 摆动工艺参数
/// </summary>
struct SWeavingProcess {
  /// <summary>
  /// 摆弧类型, [0, 1, 2, 3]
  /// </summary>
  int32_t type;

  /// <summary>
  /// 振幅(左）, [0, 100]
  /// </summary>
  double leftAmplitude_mm;

  /// <summary>
  /// 振幅(右）, [0, 100]
  /// </summary>
  double rightAmplitude_mm;

  /// <summary>
  /// 频率Hz, [0, 10]
  /// </summary>
  double frequency;

  /// <summary>
  /// 左停留时间, [0, 10000]
  /// </summary>
  int32_t leftStop_ms;

  /// <summary>
  /// 右停留时间, [0, 10000]
  /// </summary>
  int32_t rightStop_ms;

  /// <summary>
  /// 三角形高（月牙半径）
  /// </summary>
  double altitudeAmplitude_mm;

  /// <summary>
  /// 三角形端点停留时间
  /// </summary>
  int32_t altitudeStop_ms;

  /// <summary>
  /// 月牙类型
  /// </summary>
  int32_t crescentType;

  /// <summary>
  /// 摆弧启动方向
  /// </summary>
  bool isQuadrantNegative;

  /// <summary>
  /// 停留时机器人运动还是停止
  /// </summary>
  bool isMoveStop;

  /// <summary>
  /// 保留字段，无意义
  /// </summary>
  bool reserved[2];
};

typedef SWeavingProcess SWeavingProcessParam;

/// <summary>
/// 多层多道工艺参数
/// </summary>
struct SMPProcessParam {
  /// <summary>
  /// 工艺号, [0, 999]
  /// </summary>
  int32_t processId;
  /// <summary>
  /// 焊接总道数, [1, 999]
  /// </summary>
  int32_t totalTrackCount;
  /// <summary>
  /// 摆动类型, [0,1,2,3]
  /// </summary>
  int32_t weavingType;
  /// <summary>
  /// 焊缝类型, [0, 1]
  /// </summary>
  int32_t seamType;
  /// <summary>
  /// 轨迹类型, [0, 1]
  /// </summary>
  int32_t trackType;
  /// <summary>
  /// z方向参考坐标系, [0, 1, 2,3]
  /// </summary>
  int32_t coordZRef;
  /// <summary>
  /// 限制角度, [0, 90]
  /// </summary>
  double limitAngle;
  /// <summary>
  /// X坐标旋转角度, [-180, 180]
  /// </summary>
  double xRotation;
};

/// <summary>
/// 多层多道工艺/每层道参数
/// </summary>
struct SMPProcessTrackParam {
  /// <summary>
  /// 起弧电流, [0, 1000]
  /// </summary>
  double arcCurr_a;

  /// <summary>
  /// 起弧电压,  [-999, 999]
  /// </summary>
  double arcVolt_v;

  /// <summary>
  /// 起弧时间, [0, 9999]
  /// </summary>
  double arcTime_s;

  /// <summary>
  /// 焊接电流, [0, 1000]
  /// </summary>
  double weldingCurr_a;

  /// <summary>
  /// 焊接电压, [-999, 999]
  /// </summary>
  double weldingVolt_v;

  /// <summary>
  /// 焊接速度, [0, 50]
  /// </summary>
  double weldingSpeed_mm_s;

  /// <summary>
  /// 收弧电流, [0, 1000]
  /// </summary>
  double craterCurr_a;

  /// <summary>
  /// 收弧电压, [-999, 999]
  /// </summary>
  double craterVolt_v;

  /// <summary>
  /// 收弧时间, [0, 9999]
  /// </summary>
  double craterTime_s;

  /// <summary>
  /// 摆动左振幅, [0, 100]
  /// </summary>
  double swingLeftAptitude_mm_rad;

  /// <summary>
  /// 摆动右振幅, [0, 100]
  /// </summary>
  double swingRightAptitude_mm_rad;

  /// <summary>
  /// 摆动频率, [0, 6] hz
  /// </summary>
  double swingFrequency;

  /// <summary>
  /// 左停留时间, [0, 9999] ms
  /// </summary>
  double leftDwellTime;

  /// <summary>
  /// 右停留时间, [0, 9999] ms
  /// </summary>
  double rightDwellTime;

  /// <summary>
  /// 停留方式, [0, 1, 3]
  /// </summary>
  int32_t dwellMethod;

  /// <summary>
  /// 摆动方向, [0, 1, 2]
  /// </summary>
  int32_t weaveDirection;

  /// <summary>
  /// 三角形高,
  /// </summary>
  double triangleHeight_mm;
  /// <summary>
  /// 三角形顶点停留时间
  /// </summary>
  double triangleEndDwellTime_s;

  /// <summary>
  /// 月牙摆方向
  /// </summary>
  int32_t crescentSwingDirection;

  /// <summary>
  /// 焊接线前后, [-1000, 1000]
  /// </summary>
  double xOffset_mm;

  /// <summary>
  /// 焊接线左右, [-1000, 1000]
  /// </summary>
  double yOffset_mm;

  /// <summary>
  /// 焊接线上下, [-1000, 1000]
  /// </summary>
  double zOffset_mm;

  /// <summary>
  /// 梯形开始, [-1000, 1000]
  /// </summary>
  double startPoint_xOff_mm;

  /// <summary>
  /// 梯形结束, [-1000, 1000]
  /// </summary>
  double endPoint_xOff_mm;

  /// <summary>
  /// 倾角, [-40, 40]
  /// </summary>
  double inclination_deg;

  /// <summary>
  /// 前进角, [-85, 85]
  /// </summary>
  double forwardAngle_deg;
};

/// <summary>
/// 焊接参数服务接口：包括焊接工艺，摆弧工艺，多道多道工艺
/// </summary>
class IWeldService : public IService {
public:
  /// <summary>
  /// 获取焊接号的数量
  /// </summary>
  /// <param name="count">返回焊接工艺号的数量</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getWeldingProcessNumber(size_t& count) = 0;

  /// <summary>
  /// 根据索引，读取焊接工艺参数
  /// </summary>
  /// <param name="index">焊接工艺号索引</param>
  /// <param name="param">返回焊接工艺参数</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getWeldingProcess(size_t index, SWeldingProcess& param) = 0;

  /// <summary>
  /// 根据索引，修改焊接工艺参数
  /// </summary>
  /// <param name="index">焊接工艺号索引</param>
  /// <param name="param">要设置的焊接工艺参数</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setWeldingProcess(size_t index, SWeldingProcess const& param) = 0;

  /// <summary>
  /// 获取摆弧工艺号的数量
  /// </summary>
  /// <param name="count">返回摆弧工艺的数量</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getWeavingProcessNumber(size_t& count) = 0;

  /// <summary>
  /// 根据索引，读取摆弧工艺参数
  /// </summary>
  /// <param name="index">摆弧工艺号索引</param>
  /// <param name="param">返回摆弧工艺参数</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getWeavingProcess(size_t index, SWeavingProcess& param) = 0;

  /// <summary>
  /// 根据索引，设置摆弧工艺参数
  /// </summary>
  /// <param name="index">摆弧工艺号索引</param>
  /// <param name="param">要设置的摆弧工艺参数</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setWeavingProcess(size_t index, SWeavingProcess const& param) = 0;

  /// <summary>
  /// 多层多道工艺参数的数量
  /// </summary>
  /// <param name="count">返回多层多道工艺号数量</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getMPProcessNumber(size_t& count) = 0;

  /// <summary>
  /// 根据索引号，读取多层多道工艺的参数
  /// </summary>
  /// <param name="index">多层多道工艺号索引</param>
  /// <param name="param">返回多层多道工艺参数</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getMPProcess(size_t index, SMPProcessParam& param) = 0;

  /// <summary>
  /// 根据索引，设置多道多道工艺的参数
  /// </summary>
  /// <param name="index">多层多道工艺号索引</param>
  /// <param name="param">返回多层多道工艺参数</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setMPProcess(size_t index, SMPProcessParam const& param) = 0;

  /// <summary>
  /// 读取指定的多层多道工艺号的层道工艺参数
  /// </summary>
  /// <param name="processId">多道多道工艺号</param>
  /// <param name="paramArray">多层多道工艺参数数组</param>
  /// <param name="trackBufCount">in/out,传入参数数组数量，传出实际使用的数组数量</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// \note
  /// 如果传paramArray为NULL，trackBuffCount, 则返回需要paramArray需要的空间大小 内存资源由调用者管理
  virtual bool getMPProcessTrack(size_t processId, SMPProcessTrackParam* paramArray, size_t& trackBufCount) = 0;

  /// <summary>
  /// 设置指定的多层多道工艺号的层道工艺参数
  /// </summary>
  /// <param name="processId">多层多道工艺号</param>
  /// <param name="paramArray">多层多道层道参数数据</param>
  /// <param name="trackBufCount">paramArray的数据数量</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setMPProcessTrack(size_t processId, SMPProcessTrackParam const* paramArray, size_t trackBufCount) = 0;

  /// <summary>
  /// 焊接复位
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool reset() = 0;

  /// <summary>
  /// 获取焊机的反馈电流
  /// </summary>
  /// <param name="current">反馈电流值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getFeedbackCurrent(int32_t& current) = 0;

  /// <summary>
  /// 获取焊机的反馈电压
  /// </summary>
  /// <param name="voltage">反馈电压值</param>
  /// - true: 设置成功
  /// - false: 设置失败
  /// <returns></returns>
  virtual bool getFeedbackVoltage(double& voltage) = 0;

  /// <summary>
  /// 焊接过程中实时调整焊接电流
  /// </summary>
  /// <param name="delta">变化的电流值，在当前电流上叠加</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool adjustCurrent(int32_t delta) = 0;

  /// <summary>
  /// 焊接过程中实时调整焊接电压
  /// </summary>
  /// <param name="delta">变化的电压值，在当前电流上叠加</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool adjustVoltage(double delta) = 0;

  /// <summary>
  /// 焊接有效
  /// </summary>
  /// <param name="enable">焊接是否有效</param>
  /// - true: 设置成功
  /// - false: 设置失败
  virtual bool setWeldEnable(bool enable) = 0;
};
}  // namespace Crp

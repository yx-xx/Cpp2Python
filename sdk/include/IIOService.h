///
/// @file IIOService.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2024, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

#include "IService.h"

namespace Crp {

/// IIOService接口ID，<see cref=CSDKService::getService />
#define ID_IO_SERVICE "EE2C547B-B554-4DD1-B9FE-EE84955EAC60"

/// <summary>
/// IO读写接口
/// </summary>
class IIOService : public IService {
public:
  virtual ~IIOService() = default;

  // ---------------------------------------------------------------------------
  /// <summary>
  /// 系统输入SX的最大数量
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual int32_t getSXCount() = 0;

  /// <summary>
  /// 读取SX
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">SX返回值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getSX(size_t index, bool& value) = 0;

  /// ---------------------------------------------------------------------------
  /// <summary>
  /// 系统输出
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual int32_t getSYCount() = 0;

  /// <summary>
  ///
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">SY返回值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getSY(size_t index, bool& value) = 0;

  /// ---------------------------------------------------------------------------
  /// <summary>
  /// 输入
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual int32_t getXCount() = 0;

  /// <summary>
  ///
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">X返回值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getX(size_t index, bool& value) = 0;

  /// ---------------------------------------------------------------------------
  /// <summary>
  /// 输出
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual int32_t getYCount() = 0;
  /// <summary>
  /// 读取Y输出值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">Y返回值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getY(size_t index, bool& value) = 0;
  /// <summary>
  /// 写入Y输出值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">设置输出值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setY(size_t index, bool value) = 0;

  /// ---------------------------------------------------------------------------
  /// <summary>
  /// 辅助继电器
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual int32_t getMCount() = 0;

  /// <summary>
  /// 读取M值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">M返回值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getM(size_t index, bool& value) = 0;

  /// <summary>
  /// 写入M值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">M返回值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setM(size_t index, bool value) = 0;

  // ---------------------------------------------------------------------------
  /// <summary>
  /// 系统辅助继电器
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual int32_t getSMCount() = 0;

  /// <summary>
  /// 设置SM值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">SM返回值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getSM(size_t index, bool& value) = 0;

  /// ---------------------------------------------------------------------------
  /// <summary>
  /// 模拟组输入
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual int32_t getAINCount() = 0;

  /// <summary>
  /// 读取模组输入值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">读取AIN值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getAIN(size_t index, double& value) = 0;

  /// <summary>
  /// 设置模拟组输入值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">设置模拟组输入值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setAIN(size_t index, double value) = 0;

  /// ---------------------------------------------------------------------------
  /// <summary>
  /// 模拟组输出
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual int32_t getAOTCount() = 0;

  /// <summary>
  /// 读取组输出值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">读取值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getAOT(size_t index, double& value) = 0;

  /// <summary>
  /// 设置模拟组输出值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">设置值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setAOT(size_t index, double value) = 0;

  /// ---------------------------------------------------------------------------
  /// <summary>
  /// 组输入
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual int32_t getGINCount() = 0;

  /// <summary>
  /// 获取组输入值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">读取值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getGIN(size_t index, uint32_t& value) = 0;

  /// <summary>
  /// 设置组输入值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">设置值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setGIN(size_t index, uint32_t value) = 0;

  /// ---------------------------------------------------------------------------
  /// <summary>
  /// 组输出
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual int32_t getGOTCount() = 0;

  /// <summary>
  /// 获取组输出值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">读取值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getGOT(size_t index, uint32_t& value) = 0;

  /// <summary>
  /// 设置组输出值
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="value">设置值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setGOT(size_t index, uint32_t value) = 0;
};
}  // namespace Crp

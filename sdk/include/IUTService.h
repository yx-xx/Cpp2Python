///
/// @file IUTService.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2024, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

#include "IService.h"

namespace Crp {

/// IUTService接口ID
#define ID_UT_SERVICE "F7C017DC-CCE6-4DCA-9775-F9EBC3FF3CF3"

/// <summary>
/// 用户号和工具号服务接口
/// 1. 特别注意：不要在运动的过程中，修改用户号和工具号
/// 2. 在SDK操作用户号的期间，不能通过示教器修改用户号
/// </summary>
class IUTService : public IService {
public:
  virtual ~IUTService() {}

  // --------------------------------------------------------------------------
  // User Coord System

  /// <summary>
  /// 获取用户号的数量
  /// </summary>
  /// <param name="num">数量</param>
  /// <returns>
  /// - true: 成功
  /// - false: 失败
  /// </returns>
  virtual bool getUserCount(int32_t& num) = 0;

  /// <summary>
  /// 获取当前用户号
  /// </summary>
  /// <param name="num">用户号</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getCurrentUser(int32_t& num) = 0;

  /// <summary>
  /// 设置当前用户号
  /// </summary>
  /// <param name="num">用户号</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setCurrentUser(int32_t num) = 0;

  /// <summary>
  /// 设置用户号的用户数据
  /// </summary>
  /// <param name="index">用户号</param>
  /// <param name="userdata">用户数据</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// > \attention
  /// > 不能修改0号用户, 用户0坐标系, 等同于世界坐标系
  /// > 使能状态下，禁止修改工具
  virtual bool setUser(size_t index, SUserData const& userdata) = 0;

  /// <summary>
  /// 获取用户号数据
  /// </summary>
  /// <param name="index">用户号</param>
  /// <param name="userdata">用户号数据</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getUser(size_t index, SUserData& userdata) = 0;

  /// <summary>
  /// 拷贝用户号数据
  /// </summary>
  /// <param name="from">原用户号索引</param>
  /// <param name="to">目标用户号索引</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool copyUser(size_t from, size_t to) = 0;

  // --------------------------------------------------------------------------
  // Tool Coord System

  /// <summary>
  /// 获取工具号的数量
  /// </summary>
  /// <param name="num">工具号的数量</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getToolCount(int32_t& num) = 0;

  /// <summary>
  /// 获取当前工具号
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getCurrentTool(int32_t& num) = 0;

  /// <summary>
  /// 设置当前工具号
  /// </summary>
  /// <param name="num">设置当前工具号</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setCurrentTool(int32_t num) = 0;

  /// <summary>
  /// 拷贝工具号数据
  /// </summary>
  /// <param name="from">原工具号索引</param>
  /// <param name="to">目标工具号索引</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool copyTool(size_t from, size_t to) = 0;

  /// <summary>
  /// 获取指定的工具号数据
  /// </summary>
  /// <param name="index">工具号索引</param>
  /// <param name="tooldata">获取的工具号数据</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getTool(size_t index, SToolData& tooldata) = 0;

  /// <summary>
  /// 设置指定的工具号数据
  /// </summary>
  /// <param name="index">工具号索引</param>
  /// <param name="tooldata">设置的工具号索引</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// > \attention
  /// - 不要修改0号工具，0号工具为法兰末端
  /// - 使能状态下，禁止修改工具
  virtual bool setTool(size_t index, SToolData const& tooldata) = 0;
};

}  // namespace Crp

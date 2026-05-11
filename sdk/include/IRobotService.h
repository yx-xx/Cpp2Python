///
/// @file IRobotService.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2024, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

#include "IService.h"

namespace Crp {

// IRobotService接口ID
#define ID_ROBOT_SERVICE "A5236E6F-35E4-47C9-BAB1-1FC5E1DAED1B"

/// <summary>
/// 机器人基础接口服务
/// </summary>
class IRobotService : public IService {
public:
  virtual ~IRobotService() = default;

  /// <summary>
  /// 连接机器人控制柜
  /// </summary>
  /// <param name="ip"></param>
  /// <param name="disableHardware">屏蔽示教器安全开关, 如果不屏蔽，SDK在手动模式下无法使能</param>
  /// <returns>
  /// - true: 成功
  /// - false: 失败
  /// </returns>
  /// > \attention
  /// > - 禁用安全开关的情况下，示教模式会按下使能开关，会直接上使能，不能经过“伺服准备”
  virtual bool connect(const char* ip, bool disableHardware = true) = 0;

  /// <summary>
  /// 断开连接
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool disconnect() = 0;

  /// <summary>
  /// 手动模式: 伺服准备
  /// 自动模式: 上电
  /// 远程模式: 上电
  /// </summary>
  /// <returns>
  /// - true: 成功
  /// - false: 失败
  /// </returns>
  virtual bool servoPowerOn() = 0;

  /// <summary>
  /// 下电操作
  /// </summary>
  /// <returns>
  /// - true: 成功
  /// - false: 失败
  /// </returns>
  virtual bool servoPowerOff() = 0;

  /// <summary>
  /// 是否使能
  /// </summary>
  /// <returns>
  /// - true: 已经使能
  /// - false: 未使能
  /// </returns>
  virtual bool isServoOn() = 0;

  /// --------------------------------------------------------------------------
  /// <summary>
  /// 获取整形变量(GI)的最大数量
  /// </summary>
  /// <returns>
  /// 返回数量
  /// - >0: GI的最大数量
  /// - -1: 失败或出错
  /// </returns>
  virtual int32_t getGICount() = 0;

  /// <summary>
  /// 批量读取整形变量(GI)
  /// </summary>
  /// <param name="index">开始下标</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// 根据下标和数量，返回GI的数据
  /// </returns>
  virtual bool getGI(size_t index, int32_t* data, size_t count) = 0;

  /// <summary>
  /// 读取整形变量(GI)
  /// </summary>
  /// <param name="index">索引</param>
  /// <param name="data">数据</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool getGI(size_t index, int32_t& data) {
    return getGI(index, &data, 1u);
  }

  /// <summary>
  /// 批量写入整形变量(GI)
  /// </summary>
  /// <param name="index">开始下标</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setGI(size_t index, int32_t const* data, size_t count) = 0;

  /// <summary>
  /// 写入整形变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool setGI(size_t index, int32_t const& data) {
    return setGI(index, &data, 1u);
  }

  /// --------------------------------------------------------------------------
  /// <summary>
  /// 获取浮点形数据(GR)的最大数量
  /// </summary>
  /// <returns>
  /// 返回数量
  /// -1：失败或出错
  /// </returns>
  virtual int32_t getGRCount() = 0;

  /// <summary>
  /// 批量读取浮点形变量(GR)
  /// </summary>
  /// <param name="index">开始下标</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// 返回浮点数据
  /// </returns>
  virtual bool getGR(size_t index, double* data, size_t count) = 0;

  /// <summary>
  /// 读取GR变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool getGR(size_t index, double& data) {
    return getGR(index, &data, 1u);
  }

  /// <summary>
  /// 批量写入浮点形变量(GR)
  /// </summary>
  /// <param name="index">开始下标</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setGR(size_t index, double const* data, size_t count) = 0;

  /// <summary>
  /// 写入GR变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool setGR(size_t index, double const& data) {
    return setGR(index, &data, 1u);
  }

  /// --------------------------------------------------------------------------
  /// <summary>
  /// 获取UI的最大数量
  /// </summary>
  /// <returns>
  /// 返回数量
  /// -1：失败或出错
  /// </returns>
  virtual int32_t getUICount() = 0;

  /// <summary>
  /// 批量读取UI变量(UI)
  /// </summary>
  /// <param name="index">开始下标</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// 返回整形数据
  /// </returns>
  virtual bool getUI(size_t index, int16_t* data, size_t count) = 0;

  /// <summary>
  /// 读取UI变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool getUI(size_t index, int16_t& data) {
    return getUI(index, &data, 1u);
  }

  /// <summary>
  /// 批量写入UI变量(UI)
  /// </summary>
  /// <param name="index">开始下标</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setUI(size_t index, int16_t const* data, size_t count) = 0;

  /// <summary>
  /// 设置UI变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool setUI(size_t index, int16_t const& data) {
    return setUI(index, &data, 1u);
  }

  /// --------------------------------------------------------------------------
  /// <summary>
  /// 获取B的最大数量
  /// </summary>
  /// <returns>
  /// - >0: 返回数量
  /// - -1：失败或出错
  /// </returns>
  virtual int32_t getBCount() = 0;

  /// <summary>
  /// 批量读取B变量
  /// </summary>
  /// <param name="index">起始位置</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// 返回整形数据
  /// </returns>
  virtual bool getB(size_t index, int32_t* data, size_t count) = 0;

  /// <summary>
  /// 获取B变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data">返回值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool getB(size_t index, int32_t& data) {
    return getB(index, &data, 1u);
  }

  /// <summary>
  /// 批量写入B变量
  /// </summary>
  /// <param name="index">开始下标</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setB(size_t index, int32_t const* data, size_t count) = 0;

  /// <summary>
  /// 获取B变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data">写入值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool setB(size_t index, int32_t const& data) {
    return setB(index, &data, 1u);
  }

  /// --------------------------------------------------------------------------
  /// <summary>
  /// 获取S变量的最大数量
  /// </summary>
  /// <returns>
  /// 返回数量
  /// - >0：返回S的数量
  /// - -1：失败或出错
  /// </returns>
  virtual int32_t getSCount() = 0;

  /// <summary>
  /// 获取S变量，特别注意，内存由调用者申请
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="buffer">成功后返回S变量的结果，并以'\0'结尾</param>
  /// <param name="length">in/out, 传入buffer的长度，调用成功能写入buffer被写的长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getS(size_t index, char* buffer, size_t& length) = 0;

  /// <summary>
  /// 设置S变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="s">写入值</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setS(size_t index, const char* s) = 0;

  /// --------------------------------------------------------------------------

  /// <summary>
  /// 读取C变量的数量
  /// </summary>
  /// <returns>
  /// - >0: C变量的数量
  /// - -1: 失败
  /// </returns>
  virtual int32_t getCCount() = 0;

  /// <summary>
  /// 批量读取C变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getC(size_t index, STCVariable* data, size_t count) = 0;

  /// <summary>
  /// 读取一个C变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool getC(size_t index, STCVariable& data) {
    return getC(index, &data, 1u);
  }

  /// <summary>
  /// 批量设置C变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数据长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setC(size_t index, int32_t const* data, size_t count) = 0;

  /// <summary>
  /// 设置一个C变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data">变量数据</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool setC(size_t index, int32_t const& data) {
    return setC(index, &data, 1u);
  }

  /// --------------------------------------------------------------------------

  /// <summary>
  /// 获取T变量的数量
  /// </summary>
  /// <returns>
  /// - >0: T变量的数量
  /// - -1: 失败
  /// </returns>
  virtual int32_t getTCount() = 0;

  /// <summary>
  /// 批量读取T变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getT(size_t index, STCVariable* data, size_t count) = 0;

  /// <summary>
  /// 读取一个T变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data">变量数据</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool getT(size_t index, STCVariable& data) {
    return getT(index, &data, 1u);
  }

  /// <summary>
  /// 批量设置T变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setT(size_t index, int32_t const* data, size_t count) = 0;

  /// <summary>
  /// 设置一个T变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="data">设置数据</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool setT(size_t index, int32_t const& data) {
    return setT(index, &data, 1u);
  }

  /// --------------------------------------------------------------------------
  /// <summary>
  /// 返回GP的最大数量
  /// </summary>
  /// <returns>
  /// 返回GP的最大数量
  /// </returns>
  virtual size_t getGPCapacity() = 0;

  /// <summary>
  /// 获取位置变量(GP)记录点个数
  /// </summary>
  /// <returns>
  /// - >0: 返回数量
  /// - -1: 失败或出错
  /// </returns>
  virtual int32_t getGPCount() = 0;
  /// <summary>
  /// 批量获取位置变量(GP)
  /// </summary>
  /// <param name="index">开始下标</param>
  /// <param name="pos">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// 返回机器人位置
  /// </returns>
  virtual bool getGP(size_t index, SRobotPosition* pos, size_t count) = 0;

  /// <summary>
  /// 读取一个GP变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="pos"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool getGP(size_t index, SRobotPosition& pos) {
    return getGP(index, &pos, 1u);
  }

  /// <summary>
  /// 批量写入位置变量(GP)
  /// 注意：获取的GP，一定要先记录，即setGP, 否则获取失败
  /// </summary>
  /// <param name="index">开始下标</param>
  /// <param name="pos">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setGP(size_t index, SRobotPosition const* pos, size_t count) = 0;

  /// <summary>
  /// 写入一个GP变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="pos">变量数据</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool setGP(size_t index, SRobotPosition const& pos) {
    return setGP(index, &pos, 1u);
  }

  /// 清除所有的GP变量
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool clearGP() = 0;

  ///--------------------------------------------------------------------------
  // GJ
  /// <summary>
  /// 返回GJ的最大数量
  /// </summary>
  /// <returns>
  /// 返回GJ的最大数量
  /// </returns>
  virtual size_t getGJCapacity() = 0;

  /// <summary>
  /// 获取GJ记录点个数
  /// </summary>
  /// <returns>
  /// - >0: GJ变量的数量
  /// - -1: 失败或出错
  /// </returns>
  virtual int32_t getGJCount() = 0;

  /// <summary>
  /// 批量获取关节数据(GJ)
  /// 注意：获取的GJ，一定要先记录，即setGJ, 否则获取失败
  /// </summary>
  /// <param name="index">开始下标</param>
  /// <param name="pos">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getGJ(size_t index, SJointPosition* pos, size_t count) = 0;

  /// <summary>
  /// 读取一个GJ变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="pos"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool getGJ(size_t index, SJointPosition& pos) {
    return getGJ(index, &pos, 1u);
  }

  /// <summary>
  /// 批量写入位置变量(GJ)
  /// </summary>
  /// <param name="index">开始下标</param>
  /// <param name="pos">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setGJ(size_t index, SJointPosition const* pos, size_t count) = 0;

  /// <summary>
  /// 设置一个GJ变量
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="pos"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  inline bool setGJ(size_t index, SJointPosition const& pos) {
    return setGJ(index, &pos, 1u);
  }

  /// <summary>
  /// <summary>
  /// 清除所有的GJ变量
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool clearGJ() = 0;

  /// <summary>
  /// 设置钥匙开关
  /// </summary>
  /// <param name="mode">
  /// 钥匙档位, 见<see cref="ERobotMode"/>
  /// </param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setWorkMode(int mode) = 0;

  /// <summary>
  /// 获取钥匙开关
  /// </summary>
  /// <returns>
  /// - -1: 错误的情况下
  /// - 钥匙档位, 见<see cref="ERobotMode"/>
  /// </returns>
  virtual int getWorkMode() = 0;

  /// <summary>
  /// 设置当前的坐标系
  /// </summary>
  /// <param name="coord">
  /// 当前坐标系, 见<see cref="ECoordinateSystem"/>
  /// </param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setCoordSys(int coord) = 0;

  /// <summary>
  /// 获取当前的坐标系
  /// </summary>
  /// <returns>
  /// 当前坐标系, 见<see cref="ECoordinateSystem"/>
  /// </returns>
  virtual int getCoordSys() = 0;

  /// <summary>
  /// 获取当前机器人坐标位置
  /// </summary>
  /// <param name="coord">
  /// 坐标系数据, 见<see cref="ECoordinateSystem"/>
  /// </param>
  /// <param name="buffer">数组指针</param>
  /// <param name="count">数组长度</param>
  /// <returns>
  /// 根据坐标系统返回坐标值
  /// 注意：如果长度为0，表示读取错误
  /// - 0: 关节坐标系: [J1, J2, ..., J6, ext1, ext2, ..., ext6],  count = 12
  /// - 1: 世界坐标系：[x,y,z,Rx,Ry,Rz], count = 6
  /// - 2: 直角坐标系：[x,y,z,Rx,Ry,Rz], count = 6
  /// - 3: 用户坐标系：[x,y,z,Rx,Ry,Rz], count = 6
  /// </returns>
  virtual bool getCurrentPosition(int coord, double* buffer, size_t count) = 0;

  inline bool __getCurrentPosture(int coord, SRobotPosture& pos) {
    union UBuffer {
      SRobotPosture pos;
      double        data[6];
    };

    UBuffer buffer;

    bool result = false;
    result      = getCurrentPosition(coord, buffer.data, 6);
    if (result) {
      pos = buffer.pos;
    }

    return result;
  }

  /// <summary>
  /// 获取当前的世界坐标
  /// </summary>
  /// <returns>
  /// - true
  /// - false
  /// </returns>
  inline bool getWorldPosture(SRobotPosture& pos) {
    return __getCurrentPosture(ECoordinateSystem::CS_World, pos);
  }

  /// <summary>
  /// 获取当前的基坐标
  /// </summary>
  /// <returns>
  /// - true
  /// - false
  /// </returns>
  inline bool getBasePosture(SRobotPosture& pos) {
    return __getCurrentPosture(ECoordinateSystem::CS_Base, pos);
  }

  /// <summary>
  /// 获取当前的用户坐标
  /// </summary>
  /// <returns>
  /// - true
  /// - false
  /// </returns>
  inline bool getUserPosture(SRobotPosture& pos) {
    return __getCurrentPosture(ECoordinateSystem::CS_User, pos);
  }

  /// <summary>
  /// 获取试运行模式
  /// </summary>
  /// <returns>
  /// 试运行模式, 见<see cref="EDryRunMode"/>
  /// </returns>
  virtual int getDryRunMode() = 0;

  /// <summary>
  /// 设置试运行模式
  /// </summary>
  /// <param name="mode">试运行模式, 见<see cref="EDryRunMode"/></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setDryRunMode(int mode) = 0;

  /// <summary>
  /// 获取自动运行模式
  /// </summary>
  /// <returns>
  /// 自动运行模式, 见<see cref="EAutoRunMode"/>
  /// </returns>
  virtual int getAutoRunMode() = 0;

  /// <summary>
  /// 设置自动运行模式
  /// </summary>
  /// <param name="mode">自动运行模式, 见<see cref="EAutoRunMode"/></param>
  /// <returns>
  /// - true: 成功
  /// - false: 失败
  /// </returns>
  virtual bool setAutoRunMode(int mode) = 0;

  /// <summary>
  /// 启动程序
  /// </summary>
  /// <param name="program">robot/program+文件夹程序名</param>
  /// 例如：robot/program/y.pro
  /// 注意：从0.11.4起，可以省略robot/program部分
  /// <param name="line">开始行数，从0开始</param>
  /// <returns>
  /// - true: 成功
  /// - false: 失败
  /// </returns>
  virtual bool startProgram(const char* program, int line) = 0;

  /// <summary>
  /// 停止运行程序
  /// </summary>
  /// <returns>
  /// - true: 成功
  /// - false: 失败
  /// </returns>
  virtual bool stopProgram() = 0;

  /// <summary>
  /// 恢复上次暂停的程序
  /// </summary>
  /// <param name="program">恢复的程序名</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool resumeProgram(char const* program) = 0;

  /// <summary>
  ///  程序运行状态
  /// </summary>
  /// <returns>
  /// 程序状态, 见<see cref="EProgramStatus"/>
  /// </returns>
  virtual int getProgramStatus() = 0;

  /// <summary>
  /// 是否有报警
  /// </summary>
  /// <returns>
  /// - true: 当前有报警
  /// - false: 无报警
  /// </returns>
  virtual bool hasError() = 0;

  /// <summary>
  /// 清除报警
  /// </summary>
  /// <returns>
  /// - true: 清除成功
  /// - false: 清除失败
  /// </returns>
  virtual bool clearError() = 0;

  /// <summary>
  /// 获取报警的个数
  /// </summary>
  /// <param name="count"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getErrorCount(size_t& count) = 0;

  /// <summary>
  /// 根据索引获取报警的ID
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="errId"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getErrorId(size_t index, uint32_t& errId) = 0;

  /// <summary>
  /// 根据索引获取报警消息
  /// </summary>
  /// <param name="index">变量索引</param>
  /// <param name="buffer"></param>
  /// <param name="bufferLen"></param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool getErrorMessage(size_t index, char* buffer, size_t bufferLen) = 0;

  /// <summary>
  /// 获取急停状态
  /// </summary>
  /// <returns>
  /// - true: 成功
  /// - false: 失败
  /// </returns>
  virtual bool hasEmergenceError() = 0;

  /// <summary>
  /// 特别注意：软急停， 无法与示教盒的硬急停同时使用
  /// 使用了SDK连接控制的方式，硬急停会被屏蔽, 二者无法混用：
  /// - 软急停，使用软急停复位
  /// - 硬急停，则使用硬急停复位
  /// </summary>
  /// <param name="enable">急停开或关</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool emergencyStop(bool enable) = 0;

  /// <summary>
  /// 设置自动、手动、关节速度
  /// </summary>
  /// <param name="ratio">0-100</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool setSpeedRatio(int ratio) = 0;

  /// <summary>
  /// 获取自动的速率
  /// </summary>
  /// <returns>
  /// - > 0 : 速度倍率
  /// - -1: 返回错误
  /// </returns>
  virtual int getSpeedRatio() = 0;

  /// <summary>
  /// 修改GJ999变量，并移动到GJ999
  /// </summary>
  /// <param name="pos">目标关节位置</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// \note 只在手动模式下正常工作
  virtual bool moveJ(SJointPosition const& pos) = 0;

  /// <summary>
  /// 手动模式下, 修改GP999变量，并移动到GP999
  /// </summary>
  /// <param name="pos">目标笛卡尔位置</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// \note 只在手动模式下正常工作
  virtual bool moveL(SRobotPosition const& pos) = 0;

  /// <summary>
  /// 停止运动
  /// </summary>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool stopMove() = 0;

  /// <summary>
  /// 关节点动
  /// </summary>
  /// <param name="jointIndex">0-11</param>
  /// <param name="offset">点动距离</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool jogMoveJ(size_t jointIndex, double offset) = 0;

  /// <summary>
  /// 直线点动
  /// </summary>
  /// <param name="posIndex">0-5, x,y,z,rx,ry,rz</param>
  /// <param name="offset">offset</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  virtual bool jogMoveL(size_t posIndex, double offset) = 0;

  /// <summary>
  /// 是否处于规划的运动状态，注意机械上可能处理减速停的状态
  /// </summary>
  /// <param name="isMoving">是否在规划运动中</param>
  /// <returns>获取状态成功：true, 失败: false</returns>
  /// \note 机器人处于减速停止的过程中时，会提前返回false
  virtual bool isMoving(bool& isMoving) = 0;

  /// <summary>
  /// 获取当前的关节坐标和CFG
  /// </summary>
  /// <param name="pos">当前关节坐标和CFG</param>
  /// <returns>
  /// - true
  /// - false
  /// </returns>
  /// > \attention
  /// - 注意：此方法请匆在程序运行时获取, 否则可能会出错
  virtual bool getCurrentJoint(SJointPosition& pos) = 0;

  /// <summary>
  /// 获取当前程序路径
  /// </summary>
  /// <returns>
  /// - nullptr, 如果无当前程序
  /// - 当前运行的程序名，格式为null结束的字符串
  /// </returns>
  virtual const char* getProgramPath() = 0;

  /// <summary>
  /// 获取当前运行的程序行数
  /// </summary>
  /// <returns>
  /// - -1, 出错或未运行
  /// - 当前运行的程序行数
  /// </returns>
  virtual int getProgramLine() = 0;

  /// <summary>
  /// 获取当前与机器人网络的连接状态
  /// </summary>
  /// <returns></returns>
  virtual bool isConnected() = 0;

  /// @brief 打开协作模式，开启后，用户可以按下拖动按钮进行拖动操作
  /// @param[in] enable 是否开启协作模式
  /// @return
  /// - true 设置成功
  /// - false 设置失败
  virtual bool enableCobotMode(bool enable) = 0;

  /// @brief 打开协作模式，并保持伺服使能
  /// @param [in] enable 协作模式开/关
  /// @param [in] keepServoOn 保持伺服使能
  /// @return
  /// - true 设置成功
  /// - false 设置失败
  /// @attention
  /// - 如果当前工具负载设置不正确，打开协作模式，会有起撞机风险！！！
  inline bool enableCobotMode(bool enable, bool keepServoOn) {
    bool isOk = false;
    if (enableCobotMode(enable)) {
      if (keepServoOn) {
        if (isServoOn()) {
          isOk = true;
        } else if (servoPowerOn()) {
          isOk = true;
        }
      } else {
        isOk = true;
      }
    }

    return isOk;
  }

  /// @brief 协作模式是否处于打开状态
  /// @return
  /// - true 设置成功
  /// - false 设置失败
  virtual bool isCobotModeEnabled() = 0;

  /// @brief 获取设备之间的标定关系，如果有多个标定关系，依次类推
  ///  - 0 - R1 to B1
  ///  - 1 - B1 to World
  ///  - 2 - E1 to B1
  ///  - 3 - E2 to B1
  ///  - ...
  /// @param [in] relationIdx 见上描述
  /// @param [out] pose 返回标定关系
  /// @return
  /// - EC_OK                = 0x00
  /// - EC_NetworkError      = 0x01
  /// - EC_InvalidParameter  = 0x02
  /// - EC_OutOfRange        = 0x03
  /// - EC_NotSupportMethod  = 0x06
  /// @since 1.1.0
  virtual int getDeviceRelation(size_t relationIdx, SRobotPosture* pose) = 0;
};
}  // namespace Crp

///
/// @file IFileService.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2024, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

#include "IService.h"

namespace Crp {

/// IFileService接口ID
#define ID_FILE_SERVICE "FA6C07B9-B2B5-4A3B-9768-353C949D181A"

/// <summary>
/// 程序文件服务
/// </summary>
class IFileService : public IService {
public:
  virtual ~IFileService() = default;

public:
  /// <summary>
  /// 创建程序文件夹
  /// </summary>
  /// <param name="path">要创建的文件夹路径，以`/`作为路径分隔符</param>
  /// <param name="recursive">是否递归创建，如父文件夹存在，会创建父文件夹</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// \note 传给机器人的路径以`\0`结尾的UTF-8字符串
  virtual bool mkdir(const char* path, bool recursive = false) = 0;

  /// <summary>
  /// 删除程序文件夹
  /// </summary>
  /// <param name="path">要删除的文件夹路径, 以`/`作为路径分隔符</param>
  /// <param name="recursive">是否递归创建，如父文件夹存在，会创建父文件夹</param>
  /// <returns>true: 成功false: 失败</returns>
  /// \note 传给机器人的路径以`\0`结尾的UTF-8字符串
  virtual bool rmdir(const char* path, bool recursive = false) = 0;

  /// <summary>
  /// 重命名程序文件
  /// </summary>
  /// <param name="src_path">要重命名的程序文件名</param>
  /// <param name="dst_path">重名名后的程序文件名</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// \note 传给机器人的路径以`\0`结尾的UTF-8字符串
  virtual bool rename(const char* src_path, const char* dst_path) = 0;

  /// <summary>
  /// 拷贝程序文件
  /// </summary>
  /// <param name="src_path">要拷贝的程序路径</param>
  /// <param name="dst_path">目标程序路径</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// \note 传给机器人的路径以`\0`结尾的UTF-8字符串
  virtual bool copy(const char* src_path, const char* dst_path) = 0;

  /// <summary>
  /// 删除程序文件
  /// </summary>
  /// <param name="path">要删除的程序路径</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// \note 传给机器人的路径以`\0`结尾的UTF-8字符串
  virtual bool remove(const char* path) = 0;

  /// <summary>
  /// 判定程序文件是否存在
  /// </summary>
  /// <param name="path">要检查的机器人的程序路径</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// \note 传给机器人的路径以`\0`结尾的UTF-8字符串
  virtual bool exists(const char* path) = 0;

  /// <summary>
  /// 上传程序文件
  /// </summary>
  /// <param name="local_path">本地的程序路径</param>
  /// <param name="remote_path">机器人的程序路径</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// \note 传给机器人的路径以`\0`结尾的UTF-8字符串
  virtual bool upload(const char* local_path, const char* remote_path) = 0;

  /// <summary>
  /// 下载程序文件到当前设备
  /// </summary>
  /// <param name="remote_path">机器人的程序路径</param>
  /// <param name="local_path">本地的程序路径</param>
  /// <returns>
  /// - true: 设置成功
  /// - false: 设置失败
  /// </returns>
  /// \note 传给机器人的路径以`\0`结尾的UTF-8字符串
  virtual bool download(const char* remote_path, const char* local_path) = 0;
};

}  // namespace Crp

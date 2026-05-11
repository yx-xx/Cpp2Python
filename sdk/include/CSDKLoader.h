///
/// @file CSDKLoader.h
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2024, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#pragma once

#include <cassert>  // assert
#include <cstring>  // strcmp

#include <iostream>
#include <string>
#include <map>

// clang-format off
#ifdef _WIN32
# include <Windows.h>
# define __STDCALL __stdcall
# define ROBOT_SERVICE_NAME "RobotService.dll"
#else
# include <dlfcn.h>
# define __STDCALL
# define ROBOT_SERVICE_NAME "libRobotService.so"
#endif
// clang-format on

namespace Crp {
class IService;

/// <summary>
/// SDK接口加载辅助类
/// </summary>
class CSDKLoader {
private:
  typedef void*(__STDCALL* fn_createInterface)(const char* id);
  typedef void(__STDCALL* fn_destroyInterface)(void* api);

public:
  /// <summary>
  /// 构造函数
  /// </summary>
  /// <param name="sdkDllPath">指定DLL的路径</param>
  CSDKLoader(std::string const& sdkDllPath)
      : mSdkDllPath(sdkDllPath)
      , mhModule(NULL)
      , mCreator(NULL)
      , mDeleter(NULL)
      , mServiceList() {}

  ~CSDKLoader() {
    deinitialize();
  }

  /// <summary>
  /// 初始化DLL接口
  /// </summary>
  /// <param name="isolated_namespace">
  /// Linux+glibc 下为 true 时使用 dlmopen 新建链接命名空间，使同一路径的 .so
  /// 再加载一份独立的全局状态（双机必备）。默认 false 与普通 dlopen 一致。
  /// </param>
  /// <returns></returns>
  bool initialize(bool isolated_namespace = false) {
#ifdef _WIN32
    (void)isolated_namespace;
    mhModule = LoadLibraryA(mSdkDllPath.c_str());
#else
    mhModule = nullptr;
    if (isolated_namespace) {
#if defined(__linux__) && defined(__GLIBC__)
      mhModule = ::dlmopen(LM_ID_NEWLM, mSdkDllPath.c_str(), RTLD_NOW | RTLD_LOCAL);
      if (!mhModule) {
        std::cerr << "[CSDKLoader] error: dlmopen (isolated) failed: " << ::dlerror() << "\n";
        return false;
      }
#else
      std::cerr << "[CSDKLoader] warning: no dlmopen on this libc; falling back to dlopen (dual-arm may conflict)\n";
#endif
    }
    if (!mhModule) {
      mhModule = ::dlopen(mSdkDllPath.c_str(), RTLD_LAZY);
      if (!mhModule) {
        return false;
      }
    }
#endif

    if (!mhModule) {
      return false;
    }

#ifdef _WIN32
#define GET_FUNC_ADDRESS GetProcAddress
#else
#define GET_FUNC_ADDRESS dlsym
#endif

    mCreator = reinterpret_cast<fn_createInterface>(GET_FUNC_ADDRESS(mhModule, "createInterface"));
    if (!mCreator) {
      return false;
    }

    mDeleter = reinterpret_cast<fn_destroyInterface>(GET_FUNC_ADDRESS(mhModule, "destroyInterface"));
    if (!mDeleter) {
      return false;
    }

    return true;
  }

  /// <summary>
  /// 销毁创建的资源(接口、句柄)
  /// </summary>
  void deinitialize() {
    if (mDeleter) {
      std::map<std::string, IService*>::iterator it = mServiceList.begin();
      for (; it != mServiceList.end(); ++it) {
        mDeleter(it->second);
      }

      mServiceList.clear();
    }

    if (mhModule) {
#ifdef _WIN32
      (void)FreeLibrary(mhModule);
#else
      ::dlclose(mhModule);
#endif
      mhModule = NULL;
    }

    mCreator = NULL;
    mDeleter = NULL;
  }

  /// <summary>
  /// 根据接口ID, 获取接口服务，如果接口未被创建, 自动创建接口，内存由CSDKLoader管理
  /// </summary>
  /// <typeparam name="T">接口类，如IRobotService</typeparam>
  /// <param name="serviceId">接口ID, 如ID_ROBOT_SERVICE</param>
  /// <returns>
  /// - 成功返回T*接口指针，内存由dll管理，生命周期与CSDKLoader一致
  /// - 失败返回nullptr
  /// </returns>
  /// \note 注意接口类与接口ID要保持一致
  /// @attention 此函数获取的接口内存由CSDKLoader管理, 在CSDKLoader析构时被自动释放。
  template <typename T>
  T* getService(const char* serviceId) {
    if (!mCreator || !mDeleter) {
      return NULL;
    }

    std::map<std::string, IService*>::const_iterator it = mServiceList.find(serviceId);

    if (it != mServiceList.end()) {
      return (T*)(it->second);
    } else {
      T* service = reinterpret_cast<T*>(mCreator(serviceId));
      if (service != NULL) {
        bool is_matched = strcmp(service->serviceId(), serviceId) == 0;
        assert(is_matched && "T vs serviceId are not matched, please check your code!");
        if (!is_matched) {
          mDeleter(service);
          service = NULL;
        }
      }

      if (service != NULL) {
        IService* created_service = dynamic_cast<IService*>(service);
        if (created_service) {
          mServiceList[serviceId] = created_service;
        } else {
          mDeleter(service);
          service = NULL;
        }
      }

      return service;
    }
  }

  /// <summary>
  /// 根据接口ID, 创建接口服务
  /// </summary>
  /// <typeparam name="T">接口类，如IRobotService</typeparam>
  /// <param name="serviceId">接口ID, 如ID_ROBOT_SERVICE</param>
  /// <returns>
  /// - 成功返回T*接口指针，内存由用户管理，生命周期由用户管理
  /// - 失败返回nullptr
  /// </returns>
  /// \note 注意接口类与接口ID要保持一致
  /// @attention 接口创建的内存由用户管理, 释放的接口为 @see deleteService, 如未正常释放，会造成内存泄露
  template <typename T>
  T* createService(const char* serviceId) {
    if (!mCreator || !mDeleter) {
      return NULL;
    }

    T* service = reinterpret_cast<T*>(mCreator(serviceId));
    if (service != NULL) {
      bool is_matched = strcmp(service->serviceId(), serviceId) == 0;
      assert(is_matched && "T vs serviceId are not matched, please check your code!");
      if (!is_matched) {
        mDeleter(service);
        service = NULL;
      }
    }

    if (service != NULL) {
      IService* created_service = dynamic_cast<IService*>(service);
      if (!created_service) {
        mDeleter(service);
        service = NULL;
      }
    }

    return service;
  }

  /// <summary>
  /// 删除由用户创建的服务接口
  /// </summary>
  /// <typeparam name="T">接口类型</typeparam>
  /// <param name="service">服务接口</param>
  template <typename T>
  void deleteService(T* service) {
    if (!mDeleter) {
      return;
    }

    mDeleter(service);
    service = NULL;
  }

  /// <summary>
  /// 返回已创建的服务数量
  /// </summary>
  /// <returns>服务数量</returns>
  size_t serviceSize() const {
    return mServiceList.size();
  }

private:
  std::string mSdkDllPath;
#ifdef _WIN32
  HMODULE mhModule;
#else
  void* mhModule;
#endif
  fn_createInterface               mCreator;
  fn_destroyInterface              mDeleter;
  std::map<std::string, IService*> mServiceList;
};
}  // namespace Crp

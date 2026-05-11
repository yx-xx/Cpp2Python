///
/// @file it_uploadfile.cpp
/// @author 龙燕 longyan@crprobot.com
/// @copyright (c) 2025, Chengdu CRP Robot Technology CO., LTD.
/// All rights reserved.
/// @brief
///

#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <thread>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "CSDKLoader.h"
#include "IRobotService.h"
#include "IFileService.h"

constexpr char const* ROBOT_SERVICE_DLL = ROBOT_SERVICE_NAME;

void signal_handler(int signal) {
  (void)signal;
  printf("signal: %d => stop program\n", signal);
}

int main(int argc, const char* argv[]) {
  if (argc < 3) {
    printf("usage: \n it_multi_instance [robot ip1] [robot ip2]\n");
    return -1;
  }

  const char* robot_ip_1 = argv[1];
  const char* robot_ip_2 = argv[2];

  signal(SIGINT, signal_handler);
  signal(SIGABRT, signal_handler);
  signal(SIGTERM, signal_handler);

  Crp::CSDKLoader loader_1(ROBOT_SERVICE_DLL);
  Crp::CSDKLoader loader_2(ROBOT_SERVICE_DLL);

  if (!loader_1.initialize()) {
    printf("Fail to initialize");
    return -1;
  }

  if (!loader_2.initialize()) {
    printf("Fail to initialize");
    return -1;
  }

  Crp::IRobotService* robot_service_1 = loader_1.getService<Crp::IRobotService>(ID_ROBOT_SERVICE);
  // 第二台机器人必须使用第二个 loader 实例，否则会与第一台共用一个 SDK 上下文（易引发异常/索引错误）
  Crp::IRobotService* robot_service_2 = loader_2.getService<Crp::IRobotService>(ID_ROBOT_SERVICE);

  if (robot_service_1 == nullptr) {
    printf("Fail to create service 1\n");
    return -1;
  }

  if (robot_service_2 == nullptr) {
    printf("Fail to create service 2\n");
    return -1;
  }

  if (!robot_service_1->connect(robot_ip_1)) {
    printf("Fail to connect robot 1\n");
    return -1;
  }

  if (!robot_service_2->connect(robot_ip_2)) {
    printf("Fail to connect robot 2\n");
    return -1;
  }

  Crp::IFileService* file_service_1 = loader_1.getService<Crp::IFileService>(ID_FILE_SERVICE);
  Crp::IFileService* file_service_2 = loader_2.getService<Crp::IFileService>(ID_FILE_SERVICE);

  if (!file_service_1) {
    printf("Fail to connect robot 2\n");
    return -1;
  }

  if (!file_service_2) {
    printf("Fail to connect robot 2\n");
    return -1;
  }

  printf("fs 1: %p\n", file_service_1);
  printf("fs 2: %p\n", file_service_2);

  return 0;
}

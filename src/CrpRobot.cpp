#include "CrpRobot.h"
#include <chrono>
#include <thread>
#include <stdexcept>
#include <cstring> // for memset
#include <iostream>

namespace Crp {
CrpRobot::CrpRobot() 
    : loader(nullptr)
    , robot(nullptr)
    , connected(false)
    , servo_on(false) {
    // 初始化SDK加载器（默认加载RobotService库）
    loader = new CSDKLoader(ROBOT_SERVICE_NAME);
}

CrpRobot::~CrpRobot() {
    // 注意：不要在析构时自动断开连接（disconnect）。
    // 自动断开会导致 Python 对象被回收时连接被意外关闭，
    // 从而不能达到“下电但保持连接”的使用需求。
    //
    // 仅释放 loader 资源（如果需要完整释放 SDK，请显式调用 disconnect()）。
    if (loader) {
        delete loader;
        loader = nullptr;
    }
}

bool CrpRobot::connect(const std::string& ip, int retry_times) {
    // 断开已有连接
    if (connected) disconnect();

    // 初始化SDK
    if (!loader->initialize()) {
        std::cerr << "[CrpRobot] error: SDK初始化失败！\n";
        return false;
    }

    // 获取机器人服务接口
    robot = loader->getService<IRobotService>(ID_ROBOT_SERVICE);
    if (!robot) {
        std::cerr << "[CrpRobot] error: 无法获取机器人服务接口\n";
        return false;
    }

    // 重试连接逻辑
    for (int i = 0; i < retry_times; ++i) {
        std::cout << "[CrpRobot] info: 第" << i + 1 << "次连接机器人: " << ip << "\n";
        // 关键参数：disableHardware=true（禁用硬件安全开关校验）
        if (robot->connect(ip.c_str(), true)) {
            connected = true;
            // 连接成功后切换到手动模式（上电前提）
            if (switch_to_manual_mode()) {
                std::cout << "[CrpRobot] info: 连接机器人并切换到手动模式\n";
                return true;
            } else {
                std::cerr << "[CrpRobot] error: 连接成功但切换手动模式失败，重试连接...\n";
                robot->disconnect();
                connected = false;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cerr << "[CrpRobot] error: 连接机器人失败（IP: " << ip << "）\n";
    return false;
}

void CrpRobot::disconnect() {
    if (connected && robot) {
        // 下电并断开连接
        robot->servoPowerOff();
        robot->disconnect();
        std::cout << "[CrpRobot] info: 机器人已断开连接\n";
    }
    connected = false;
    servo_on = false;
    if (loader) {
        // 断开连接时一并反初始化 loader（如果你希望保持 loader 活着，可注释此行）
        loader->deinitialize();
    }
}

bool CrpRobot::switch_work_mode(ERobotMode mode) {
    if (!robot || !connected) return false;
    return robot->setWorkMode(static_cast<int>(mode));
}

int CrpRobot::get_work_mode() const {
    if (!robot || !connected) return -1;
    return robot->getWorkMode();
}

bool CrpRobot::switch_to_manual_mode() {
    return switch_work_mode(RM_Manual);
}

bool CrpRobot::servo_power_on(int retry_times) {
    if (!connected) {
        std::cerr << "[CrpRobot] error: 未连接机器人，无法上电\n";
        return false;
    }

    // 确保在手动模式
    if (!is_manual_mode()) {
        std::cerr << "[CrpRobot] error: 不在手动模式，无法上电\n";
        return false;
    }

    // 重试上电：一旦检测到上电成功就立即返回 true（不再重复尝试）
    for (int i = 0; i < retry_times; ++i) {
        std::cout << "[CrpRobot] info: 第" << i + 1 << "次尝试上电\n";
        if (robot->servoPowerOn()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            if (robot->isServoOn()) {
                servo_on = true;
                std::cout << "[CrpRobot] info: 伺服上电完成\n";
                return true; // <-- 成功立即返回，避免重复上电日志
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cerr << "[CrpRobot] error: 伺服上电失败\n";
    return false;
}

bool CrpRobot::servo_power_off() {
    if (!connected || !servo_on) return false;
    if (robot->servoPowerOff()) {
        servo_on = false;
        std::cout << "[CrpRobot] info: 伺服下电完成\n";
        return true;
    }
    return false;
}

std::map<std::string, double> CrpRobot::read_joints() {
    std::map<std::string, double> joints;
    if (!connected) return joints;

    SJointPosition current_joints;
    if (robot->getCurrentJoint(current_joints)) {
        joints["j1"] = current_joints.body[0];
        joints["j2"] = current_joints.body[1];
        joints["j3"] = current_joints.body[2];
        joints["j4"] = current_joints.body[3];
        joints["j5"] = current_joints.body[4];
        joints["j6"] = current_joints.body[5];
    }
    return joints;
}

std::vector<double> CrpRobot::read_end_pose() {
    std::vector<double> pose(6, 0.0);
    if (!connected) return pose;

    SRobotPosture current_pose;
    if (robot->getWorldPosture(current_pose)) {
        pose[0] = current_pose.x;
        pose[1] = current_pose.y;
        pose[2] = current_pose.z;
        pose[3] = current_pose.Rx;
        pose[4] = current_pose.Ry;
        pose[5] = current_pose.Rz;
    }
    return pose;
}

bool CrpRobot::movej_absolute(const std::map<std::string, double>& target_joints, 
                                 int wait_ms) {
    if (!connected || !servo_on || !is_manual_mode()) return false;

    // 构造目标关节数据
    SJointPosition target;
    std::memset(&target, 0, sizeof(target));
    target.body[0] = target_joints.at("j1");
    target.body[1] = target_joints.at("j2");
    target.body[2] = target_joints.at("j3");
    target.body[3] = target_joints.at("j4");
    target.body[4] = target_joints.at("j5");
    target.body[5] = target_joints.at("j6");

    // 执行关节运动
    if (!robot->moveJ(target)) {
        std::cerr << "[CrpRobot] error: 发送MoveJ指令失败\n";
        return false;
    }

    // 等待运动完成
    if (!wait_for_movement(wait_ms)) {
        std::cerr << "[CrpRobot] error: 运动超时\n";
        return false;
    }

    return true;
}

bool CrpRobot::movel_absolute(const std::vector<double>& target_pose, 
                                 int wait_ms) {
    if (!connected || !servo_on || !is_manual_mode() || target_pose.size() != 6) return false;

    // 构造目标位姿数据
    SRobotPosition target;
    std::memset(&target, 0, sizeof(target));
    target.x = target_pose[0];
    target.y = target_pose[1];
    target.z = target_pose[2];
    target.Rx = target_pose[3];
    target.Ry = target_pose[4];
    target.Rz = target_pose[5];

    // 执行直线运动
    if (!robot->moveL(target)) {
        std::cerr << "[CrpRobot] error: 发送MoveL指令失败\n";
        return false;
    }

    // 等待运动完成
    if (!wait_for_movement(wait_ms)) {
        std::cerr << "[CrpRobot] error: 运动超时\n";
        return false;
    }

    return true;
}

bool CrpRobot::wait_for_movement(int timeout_ms) {
    auto start = std::chrono::steady_clock::now();
    while (true) {
        // 检查是否超时
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start).count();
        if (elapsed > timeout_ms) {
            return false;
        }

        // 检查是否停止运动
        bool is_moving;
        if (robot->isMoving(is_moving) && !is_moving) {
            return true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool CrpRobot::stop_move() {
    if (!connected) return false;
    return robot->stopMove();
}
}  // namespace Crp

#pragma once

#include <string>
#include <map>
#include <vector>
#include "CSDKLoader.h"
#include "IRobotService.h"
#include "RobotTypes.h"

namespace Crp {
class CrpRobot {
public:
    CrpRobot();
    ~CrpRobot();

    // 连接机器人（返回是否成功）
    bool connect(const std::string& ip = "192.168.0.100", int retry_times = 3);
    
    // 断开连接（会尝试下电并断开）
    void disconnect();
    
    // 检查是否连接
    bool is_connected() const { return connected; }
    
    // 伺服上电（成功后立即返回，不会在成功后继续多余重试）
    bool servo_power_on(int retry_times = 3);
    
    // 伺服下电（仅下电，不断开连接）
    bool servo_power_off();
    
    // 检查伺服是否上电
    bool is_servo_on() const { return servo_on; }
    
    // 切换工作模式
    bool switch_work_mode(ERobotMode mode);
    
    // 获取当前工作模式
    int get_work_mode() const;
    
    // 检查是否为手动模式
    bool is_manual_mode() const { return get_work_mode() == RM_Manual; }
    
    // 绝对关节运动（MoveJ）
    bool movej_absolute(const std::map<std::string, double>& target_joints, 
                       int wait_ms = 6000);
    
    // 绝对直线运动（MoveL）
    bool movel_absolute(const std::vector<double>& target_pose, 
                       int wait_ms = 6000);
    
    // 读取当前关节角度
    std::map<std::string, double> read_joints();
    
    // 读取末端位姿
    std::vector<double> read_end_pose();
    
    // 停止运动
    bool stop_move();

private:
    CSDKLoader* loader;               // SDK加载器
    IRobotService* robot;             // 机器人服务接口
    bool connected;                   // 连接状态
    bool servo_on;                    // 伺服使能状态
    
    // 内部模式切换辅助函数
    bool switch_to_manual_mode();
    
    // 等待运动完成
    bool wait_for_movement(int timeout_ms);
};
}  // namespace Crp

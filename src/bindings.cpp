#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "CrpRobot.h"

namespace py = pybind11;

PYBIND11_MODULE(CrpRobotPy, m) {
    m.doc() = "Crp Python API";

    // 导出枚举
    py::enum_<Crp::ERobotMode>(m, "RobotMode")
        .value("Manual", Crp::RM_Manual)    // 手动模式（MoveL必需）
        .value("Auto", Crp::RM_Playing)     // 自动模式
        .value("Remote", Crp::RM_Remote)    // 远程模式
        .export_values();

    py::enum_<Crp::ECoordinateSystem>(m, "CoordinateSystem")
        .value("Joint", Crp::CS_Joint)      // 关节坐标系
        .value("World", Crp::CS_World)      // 世界坐标系（默认）
        .value("Base", Crp::CS_Base)        // 基坐标系
        .value("User", Crp::CS_User)        // 用户坐标系
        .value("Tool", Crp::CS_Tool)        // 工具坐标系
        .export_values();

    // 导出封装类
    py::class_<Crp::CrpRobot>(m, "CrpRobotPy")

        .def(py::init<>(), 
             "Initialize a CrpRobotPy object")

        .def("connect", &Crp::CrpRobot::connect, 
             py::arg("ip") = "192.168.0.100", 
             py::arg("retry_times") = 3,
             "Connect to the robot with the given IP address and retry times (default: 3)")
             
        .def("disconnect", &Crp::CrpRobot::disconnect, 
             "Disconnect from the robot")

        .def("is_connected", &Crp::CrpRobot::is_connected, 
             "Check if the robot is connected")

        .def("servo_power_on", &Crp::CrpRobot::servo_power_on, 
             py::arg("retry_times") = 3,
             "Power on the servo and retry times (default: 3)")
             
        .def("servo_power_off", &Crp::CrpRobot::servo_power_off, 
             "Power off the servo")

        .def("is_servo_on", &Crp::CrpRobot::is_servo_on,
             "Check if the servo is powered on")

        .def("switch_work_mode", &Crp::CrpRobot::switch_work_mode, 
             py::arg("mode"), 
             "Switch the robot's work mode")

        .def("get_work_mode", &Crp::CrpRobot::get_work_mode, 
             "Get the current work mode of the robot")

        .def("is_manual_mode", &Crp::CrpRobot::is_manual_mode, 
             "Check if the robot is in manual mode")

        .def("movej_absolute", &Crp::CrpRobot::movej_absolute,
             py::arg("target_joints"),  // 字典：{"j1": 角度, ..., "j6": 角度}
             py::arg("wait_ms") = 6000, // 等待运动完成的时间（ms）
             "绝对关节控制（MoveJ）")

        .def("movel_absolute", &Crp::CrpRobot::movel_absolute,
             py::arg("target_pose"),   // 列表：[X, Y, Z, Rx, Ry, Rz]（单位：mm/度）
             py::arg("wait_ms") = 6000,
             "绝对末端位置控制（MoveL）")

        .def("read_joints", &Crp::CrpRobot::read_joints, 
             "读取当前关节角度（返回字典：{\"j1\": 角度, ..., \"j6\": 角度}）")

        .def("read_end_pose", &Crp::CrpRobot::read_end_pose, 
             "读取当前末端位姿（返回列表：[X, Y, Z, Rx, Ry, Rz]）")

        .def("stop_move", &Crp::CrpRobot::stop_move, "紧急停止所有运动");
        
}

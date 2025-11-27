cmake_minimum_required(VERSION 3.20)

project(Cpp2Python LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Python3 COMPONENTS Development Interpreter REQUIRED)

# -------------------------------------------------------------------------
# 配置参数
# 供二次使用者覆写：cmake -S . -B build -DPY_MODULE_NAME=FooPy -DSDK_LIBS="/abs/path/libFoo.so"
# -------------------------------------------------------------------------
set(PY_MODULE_NAME "CrpRobotPy" CACHE STRING "最终生成的 Python 模块名（需与 PYBIND11_MODULE 保持一致）")
set(CORE_TARGET_NAME "CrpRobot" CACHE STRING "封装 SDK 的 C++ 静态库 target 名称")

# 核心封装代码
set(DEFAULT_CORE_SOURCES
    ${CMAKE_SOURCE_DIR}/src/CrpRobot.cpp
)
set(CORE_SOURCES "${DEFAULT_CORE_SOURCES}" CACHE STRING "封装库源码（分号分隔）")
separate_arguments(CORE_SOURCES)

# 绑定源码
set(DEFAULT_BINDING_SOURCES
    ${CMAKE_SOURCE_DIR}/src/bindings.cpp
)
set(BINDING_SOURCES "${DEFAULT_BINDING_SOURCES}" CACHE STRING "pybind11 绑定源码（分号分隔）")
separate_arguments(BINDING_SOURCES)

# SDK 头文件目录
set(DEFAULT_SDK_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/sdk/include
)
set(SDK_INCLUDE_DIRS "${DEFAULT_SDK_INCLUDE_DIRS}" CACHE STRING "SDK 头文件目录（分号分隔）")
separate_arguments(SDK_INCLUDE_DIRS)

# SDK 共享库所在目录
set(DEFAULT_SDK_LIB_DIR ${CMAKE_SOURCE_DIR}/sdk/bin)
set(SDK_LIB_DIR "${DEFAULT_SDK_LIB_DIR}" CACHE PATH "SDK 共享库所在目录")

set(DEFAULT_SDK_LIBS
    ${SDK_LIB_DIR}/libRobotService.so
)
set(SDK_LIBS "${DEFAULT_SDK_LIBS}" CACHE STRING "需要链接的 SDK 共享库（分号分隔绝对路径）")
separate_arguments(SDK_LIBS)

# pybind11 头文件目录
set(DEFAULT_PYBIND11_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/pybind11/include)
set(PYBIND11_INCLUDE_DIR "${DEFAULT_PYBIND11_INCLUDE_DIR}" CACHE PATH "pybind11 头文件目录")

# 校验依赖文件存在，方便换 SDK 时快速定位问题
foreach(REQUIRED_PATH IN LISTS SDK_LIBS)
    if(NOT EXISTS ${REQUIRED_PATH})
        message(FATAL_ERROR "SDK shared library not found: ${REQUIRED_PATH}")
    endif()
endforeach()

foreach(REQUIRED_INC IN LISTS SDK_INCLUDE_DIRS PYBIND11_INCLUDE_DIR)
    if(NOT EXISTS ${REQUIRED_INC})
        message(FATAL_ERROR "Include directory not found: ${REQUIRED_INC}")
    endif()
endforeach()

# -------------------------------------------------------------------------
# cpp类封装为静态库
# -------------------------------------------------------------------------
add_library(${CORE_TARGET_NAME} STATIC ${CORE_SOURCES})
# 启用位置无关代码
set_target_properties(${CORE_TARGET_NAME} PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
target_include_directories(${CORE_TARGET_NAME}
    PUBLIC
        ${SDK_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/src
)

# -------------------------------------------------------------------------
# 构建 Python 模块
# -------------------------------------------------------------------------
add_library(${PY_MODULE_NAME} MODULE ${BINDING_SOURCES})
target_include_directories(${PY_MODULE_NAME}
    PRIVATE
        ${PYBIND11_INCLUDE_DIR}
        ${SDK_INCLUDE_DIRS}
        # ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(${PY_MODULE_NAME}
    PRIVATE
        ${CORE_TARGET_NAME}
        Python3::Module
        ${SDK_LIBS}
)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PY_MODULE_NAME} PRIVATE pthread dl)
endif()


# -------------------------------------------------------------------------
# 构建输出目录
# -------------------------------------------------------------------------
set(TARGET_OUTPUT_DIR ${CMAKE_BINARY_DIR}/python)
set_target_properties(${PY_MODULE_NAME} PROPERTIES
    OUTPUT_NAME "${PY_MODULE_NAME}"
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${TARGET_OUTPUT_DIR}
)

if(UNIX)
    set_target_properties(${PY_MODULE_NAME} PROPERTIES
        BUILD_RPATH ${SDK_LIB_DIR}
        INSTALL_RPATH ${SDK_LIB_DIR}
    )
endif()

add_custom_command(
    TARGET ${PY_MODULE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${TARGET_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SDK_LIBS}
            ${TARGET_OUTPUT_DIR}/
    COMMENT "Copying SDK shared libraries next to the Python module"
)


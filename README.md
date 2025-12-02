# Cpp2Python

Cpp to Python with pybind11

## 依赖项

- **pybind11**：已包含在 `pybind11/` 目录中
- **SDK**：放到在 `sdk/` 目录中
- **Python3 Development**：建议激活一个conda环境使用

## 构建说明

### 1. 克隆项目

```bash
git clone <repository-url>
cd Cpp2Python
```

### 2. 配置和构建

```bash
# 创建构建目录
mkdir -p build
cd build

# 配置 CMake
cmake ..

# 编译
make
```

### 3. 构建输出

编译成功后，Python 模块将生成在 `build/python/` 目录下：
- `CrpRobotPy.so`：Python 扩展模块
- `libRobotService.so`：SDK 共享库（已自动复制）

### 4. 自定义构建参数

可以通过 CMake 参数自定义构建配置：

```bash
cmake -S . -B build \
    -DPY_MODULE_NAME=MyRobotPy \
    -DSDK_LIBS="/path/to/libCustom.so"
```

可配置参数：
- `PY_MODULE_NAME`：Python 模块名称（默认：`CrpRobotPy`）
- `CORE_TARGET_NAME`：核心库目标名称（默认：`CrpRobot`）
- `SDK_LIBS`：SDK 共享库路径（分号分隔）
- `SDK_INCLUDE_DIRS`：SDK 头文件目录（分号分隔）

## 项目结构

```
Cpp2Python/
├── CMakeLists.txt          # CMake 构建配置
├── README.md               # 项目说明文档
├── src/                    # 源代码目录
│   ├── CrpRobot.cpp       # 核心封装实现
│   └── bindings.cpp       # pybind11 绑定代码
├── sdk/                    # CRP SDK 目录
│   ├── include/           # SDK 头文件
│   └── bin/               # SDK 共享库
├── pybind11/              # pybind11 库
│   └── include/           # pybind11 头文件
└── build/                 # 构建输出目录
    └── python/            # Python 模块输出
        ├── CrpRobotPy.so  # Python 扩展模块
        └── libRobotService.so  # SDK 共享库
```

## 贡献

欢迎提交 Issue 和 Pull Request！

## 联系方式

如有问题或建议，请通过 Issue 反馈。

# Cpp2Python

Cpp to Python with pybind11

## Dependencies

- **pybind11**: Included in the `pybind11/` directory
- **SDK**: Place in the `sdk/` directory
- **Python3 Development**: It is recommended to use a conda environment

## Build Instructions

### 1. Clone the Project

```bash
git clone <repository-url>
cd Cpp2Python
```

### 2. Configure and Build

```bash
# Create build directory
mkdir -p build
cd build

# Configure CMake
cmake ..

# Compile
make
```

### 3. Build Output

After successful compilation, the Python module will be generated in the `build/python/` directory:
- `CrpRobotPy.so`: Python extension module
- `libRobotService.so`: SDK shared library (automatically copied)

### 4. Custom Build Parameters

You can customize the build configuration through CMake parameters:

```bash
cmake -S . -B build \
    -DPY_MODULE_NAME=MyRobotPy \
    -DSDK_LIBS="/path/to/libCustom.so"
```

Configurable parameters:
- `PY_MODULE_NAME`: Python module name (default: `CrpRobotPy`)
- `CORE_TARGET_NAME`: Core library target name (default: `CrpRobot`)
- `SDK_LIBS`: SDK shared library paths (semicolon-separated)
- `SDK_INCLUDE_DIRS`: SDK header file directories (semicolon-separated)

## Project Structure

```
Cpp2Python/
├── CMakeLists.txt          # CMake build configuration
├── README.md               # Project documentation
├── src/                    # Source code directory
│   ├── CrpRobot.cpp       # Core wrapper implementation
│   └── bindings.cpp       # pybind11 binding code
├── sdk/                    # CRP SDK directory
│   ├── include/           # SDK header files
│   └── bin/               # SDK shared libraries
├── pybind11/              # pybind11 library
│   └── include/           # pybind11 header files
└── build/                 # Build output directory
    └── python/            # Python module output
        ├── CrpRobotPy.so  # Python extension module
        └── libRobotService.so  # SDK shared library
```

## Contributing

Issues and Pull Requests are welcome!

## Contact

If you have any questions or suggestions, please provide feedback through Issues.


# 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(FluxStore)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加包含目录
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/src/third_party/include)

# 查找 src 目录下的源文件
file(GLOB SRC_SOURCES src/*.cc src/store/*)

link_directories(${PROJECT_SOURCE_DIR}/src/third_party/lib)

# 指定可执行文件
add_executable(FluxStore
    src/main.cc
    ${SRC_SOURCES}
    )

# 如果需要，可以添加调试信息
set(CMAKE_BUILD_TYPE Debug)

# 添加编译选项（可选）
# add_compile_options(-Wall -Wextra -pedantic)

target_link_libraries(FluxStore glog gflags unwind pthread)
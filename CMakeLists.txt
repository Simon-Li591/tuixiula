# _var 意味着自己修改
# cmake -S . -B build -GNinja
# cmake --build build

# 1、基础设置
cmake_minimum_required(VERSION 3.24)

# conan
# set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES conan_provider.cmake)

project(cxx_project LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# 使用CMake的生成器表达式来设置不同编译配置下的编译和连接选项：

# 设置编译时使用UTF-8字符编码
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 设置编译的Debug信息格式
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/Zi>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zi>")

# 设置编译器为兼容模式，否则像and, or这些alternative token就无法支持
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/permissive->")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/permissive->")

# 关闭增量链接
add_link_options("$<$<C_COMPILER_ID:MSVC>:/INCREMENTAL:NO>")
add_link_options("$<$<CXX_COMPILER_ID:MSVC>:/INCREMENTAL:NO>")

# 创建Debug信息
add_link_options("$<$<C_COMPILER_ID:MSVC>:/DEBUG>")
add_link_options("$<$<CXX_COMPILER_ID:MSVC>:/DEBUG>")

# 链接优化：消除无用的函数和数据
add_link_options("$<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/OPT:REF>")
add_link_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/OPT:REF>")

# 链接优化：执行相同的COMDAT折叠
add_link_options("$<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/OPT:ICF>")
add_link_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/OPT:ICF>")

# 操作线程需要添加之
find_package(Threads)

#　２、添加依赖
# 首先包含FetchContent功能模块
include(FetchContent)
FetchContent_Declare(
	           fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
	       GIT_TAG 10.0.0
	   GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(fmt)
# 声明Icraft-Utils的信息
# GIT_TAG 可以是分支、tag或者commit id
# FetchContent_Declare(
# 	inipp
#   	GIT_REPOSITORY https://github.com/mcmtroffaes/inipp.git
#   	GIT_TAG        develop
#   	GIT_SHALLOW    TRUE
# )
# # 构建Icraft-Utils，并将其target添加到当前作用域
# FetchContent_MakeAvailable(inipp)

# 3
# 添加动态链接库
# add_executable(cmake02 )
add_library(mthread SHARED "")
add_library(model SHARED "")
add_library(project1 SHARED "")
# 4 添加子目录
# 理论上应该在source下编写CMakeLists.txt，添加以下四个文件夹，然后在顶层添加source
add_subdirectory(source)

# 5  设置头文件路径、宏定义和依赖的链接库
# PUBLIC的意思是依赖Icraft-XIR的工程也要依赖以下的头文件路径
target_include_directories(model PUBLIC
	include
)

target_include_directories(mthread PUBLIC
	include
)

target_include_directories(project1 PUBLIC
	include
)

# PRIVATE的意思是以下宏定义只对Icraft-XIR有效，对依赖它的工程无效
target_compile_definitions(mthread PRIVATE
	_CRT_SECURE_NO_WARNINGS
)

# PUBLIC的意思是依赖Icraft-XIR的工程也要链接以下库
target_link_libraries(mthread PUBLIC
	${CMAKE_THREAD_LIBS_INIT}
	)
target_link_libraries(mthread PUBLIC 
	fmt
	 )

# 此处为icraft_xir设置别名Icraft::XIR
# 设置别名后用户可以使用Icraft::XIR来链接，更加清晰规整
# 建议为每个库设置Icraft::xx的别名
add_library(m::thread ALIAS mthread)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(tests)
endif()
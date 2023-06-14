cmake_minimum_required(VERSION 3.24)

# find_package(Catch REQUIRED)

add_executable(test_mthread "")

target_sources(test_mthread PRIVATE
	main.cpp
)


# 分别添加tests文件夹下的core、ops、custom文件夹
# 在这三个文件夹下分别有CMakeLists.txt来描述对其源文件的构建
# add_subdirectory(core)

target_link_libraries(test_mthread PRIVATE  mthread)
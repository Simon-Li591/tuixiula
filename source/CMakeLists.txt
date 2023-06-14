cmake_minimum_required(VERSION 3.24)

add_subdirectory(model )
add_subdirectory(mthread)
# 设置该路径下用于编译icraft_xir的源文件
target_sources(project1 PRIVATE
    main.cpp
    #next.cpp
)
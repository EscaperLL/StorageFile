#1.cmake verson，指定cmake版本 
 cmake_minimum_required(VERSION 3.2)
 
 #2.project name，指定项目的名称，一般和项目的文件夹名称对应
 PROJECT(test_sqrt)
 
 #3.head file path，头文件目录
 INCLUDE_DIRECTORIES(
 include
 )
 
set (_CXX_STANDARD "gnu++2a")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${_CXX_STANDARD} -g")

 #4.source directory，源文件目录
 AUX_SOURCE_DIRECTORY(.  DIR_SRCS)
 
 #5.set environment variable，设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"
 SET(TEST_MATH
 ${DIR_SRCS}
 )
 
 #6.add executable file，添加要编译的可执行文件

 ADD_EXECUTABLE(${PROJECT_NAME} ${TEST_MATH})

 target_link_libraries(${PROJECT_NAME} -lstdc++)

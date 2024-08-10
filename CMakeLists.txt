# CMake 프로그램 최소 버전
cmake_minimum_required(VERSION 3.11)

# 프로젝트 정보
project(CMakeTest)

add_executable(TestName Test.cpp)

# 추가 포함 디렉터리
target_include_directories(TestName PUBLIC ${CMAKE_SOURCE_DIR}/../../../Study_ZMQ/cppzmq-4.10.0/ ${CMAKE_SOURCE_DIR}/../../../Study_ZMQ/libzmq-4.3.5/include)
# 라이브러리 링크
target_link_libraries(TestName libzmq-v143-mt-s-4_3_5.lib  libzmq-v143-mt-4_3_5.lib)
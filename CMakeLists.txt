cmake_minimum_required(VERSION 3.12)
project(JNP6)

set(CMAKE_CXX_STANDARD 17)

add_executable(JNP6 rebelfleet.cc rebelfleet.h imperialfleet.cc imperialfleet.h battle.cc battle.h helper.cc helper.h)
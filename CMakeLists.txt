cmake_minimum_required(VERSION 3.15)
project(cmatrix C)




add_library(cmatrix src/matrix.c)
target_include_directories(cmatrix PUBLIC include)



set_target_properties(cmatrix PROPERTIES PUBLIC_HEADER "include/matrix.h")
install(TARGETS cmatrix)

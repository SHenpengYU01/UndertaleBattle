# unset(VCPKG_ROOT CACHE)
# unset(CMAKE_TOOLCHAIN_FILE CACHE)
# unset(VCPKG_TARGET_TRIPLET CACHE)
# set(CMAKE_FIND_USE_PACKAGE_REGISTRY OFF)

# if(DEFINED ENV{VCPKG_ROOT})
#     set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
#         CACHE STRING "Vcpkg toolchain file")
# elseif(DEFINED ENV{VCPKG_DEFAULT_TRIPLET})
#     set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DEFAULT_TRIPLET}/scripts/buildsystems/vcpkg.cmake"
#         CACHE STRING "Vcpkg toolchain file")
# else()
#     # 手动指定 vcpkg 路径
#     set(CMAKE_TOOLCHAIN_FILE "~/vcpkg/scripts/buildsystems/vcpkg.cmake"
#         CACHE STRING "Vcpkg toolchain file")
# endif()

cmake_minimum_required(VERSION 3.12)

project(UndertaleFight)

# 设置SFML路径 (指向你本地的SFML目录)
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")

find_package(SFML COMPONENTS graphics window audio system CONFIG REQUIRED)

add_subdirectory(src src)


#!/bin/bash

# 检查 VCPKG_ROOT 是否设置
if [ -z "${VCPKG_ROOT}" ]; then
  echo "错误：VCPKG_ROOT 环境变量未设置！"
  exit 1
fi

# 执行CMake配置命令
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE="${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" \
  -DVCPKG_MANIFEST_MODE=ON
cmake --build build --config Debug
echo "配置完成！"

# 执行CMake配置命令
cmake . -G "Ninja" -B build
cmake --build build --config Debug
echo "配置完成！"
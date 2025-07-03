#ifndef PRECOMP_H
#define PRECOMP_H

#include <iostream>
#include <array>
#include <deque>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdint>
#include <chrono>

// #include <locale> // 需要包含此头文件
#include <codecvt> // 用于字符串转换
#include <any>
#include <functional>

typedef uint32_t DWORD;

// 统一使用GetTickCount函数名
inline DWORD GetTickCount() {
    using namespace std::chrono;
    auto now = steady_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch());
    return static_cast<DWORD>(ms.count());
}
#endif
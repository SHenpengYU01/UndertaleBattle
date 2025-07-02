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

#include <functional>

// #ifdef _WIN32
//     #include <Windows.h>
// #else
//     // 使用精确的32位无符号整数类型
//     typedef uint32_t DWORD;
    
//     // 统一使用GetTickCount函数名
//     inline DWORD GetTickCount() {
//         using namespace std::chrono;
//         auto now = steady_clock::now();
//         auto ms = duration_cast<milliseconds>(now.time_since_epoch());
//         return static_cast<DWORD>(ms.count());
//     }
// #endif

typedef uint32_t DWORD;

// 统一使用GetTickCount函数名
inline DWORD GetTickCount() {
    using namespace std::chrono;
    auto now = steady_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch());
    return static_cast<DWORD>(ms.count());
}
#endif
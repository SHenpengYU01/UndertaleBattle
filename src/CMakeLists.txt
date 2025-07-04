# # 1. 指定 vcpkg 工具链（关键步骤）
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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# src/CMakeLists.txt

# 设置源文件列表
set(SOURCES
    view/mainwindow.cpp
    app/game.cpp
    common/frame.cpp
    main.cpp
    viewmodel/file_manager.cpp
    viewmodel/player.cpp
    viewmodel/gaster.cpp
    viewmodel/board.cpp
    viewmodel/gamefile.cpp
)

# 创建可执行文件
add_executable(UndertaleFight ${SOURCES})

# 设置预编译头（如果需要）
target_precompile_headers(UndertaleFight PRIVATE precomp.h)

# 链接SFML库
# target_link_libraries(UndertaleFight PRIVATE
#     SFML::Graphics
#     SFML::Window
#     SFML::Audio
#     SFML::System
# )

target_link_libraries(UndertaleFight PRIVATE
    sfml-graphics
    sfml-window
    sfml-audio
    sfml-system
)


# 在可执行文件目录创建符号链接
add_custom_command(TARGET UndertaleFight POST_BUILD
    # 创建符号链接
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "libsfml-graphics.so.2.5.1" "libsfml-graphics.so.2.5"
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "libsfml-window.so.2.5.1" "libsfml-window.so.2.5"
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "libsfml-audio.so.2.5.1" "libsfml-audio.so.2.5"
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "libsfml-system.so.2.5.1" "libsfml-system.so.2.5"
    WORKING_DIRECTORY ${SFML_ROOT}/lib
)


# 设置可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output)

# 创建资源目录
set(RESOURCES_DIR "${EXECUTABLE_OUTPUT_PATH}/assets")
file(MAKE_DIRECTORY "${RESOURCES_DIR}")

# 复制 sprites 目录到 RESOURCES_DIR/sprites/
file(COPY
    ${CMAKE_SOURCE_DIR}/src/bin/sprites/
    DESTINATION ${RESOURCES_DIR}/sprites
)

file(COPY
    ${CMAKE_SOURCE_DIR}/src/bin/fonts/
    DESTINATION ${RESOURCES_DIR}/fonts
)

file(COPY
    ${CMAKE_SOURCE_DIR}/src/bin/audio/
    DESTINATION ${RESOURCES_DIR}/audio
)


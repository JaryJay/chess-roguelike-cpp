cmake_minimum_required(VERSION 3.29)

string(REPLACE "\\" "/" VCPKG_ROOT "$ENV{VCPKG_ROOT}")

# Set the vcpkg toolchain file and C++ standard
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_CXX_STANDARD 20)

project(chess-roguelike-cpp)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)

# Add the engine submodule
add_subdirectory(external/opengl-cpp-engine)

add_executable(chess-roguelike-cpp
        src/BoardState.cpp
        src/BoardState.h
        src/main.cpp
        src/Move.h
        src/Piece.cpp
        src/Piece.h
        src/PieceType.h
        src/Team.cpp
        src/Team.h
        src/Game.cpp
        src/Game.h
        src/ArmyGenerator.cpp
        src/ArmyGenerator.h)

# Copy the shaders to the build directory
add_custom_command(
        TARGET chess-roguelike-cpp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/external/opengl-cpp-engine/shaders
        ${CMAKE_CURRENT_BINARY_DIR}/shaders)

# Copy the assets to the build directory
add_custom_command(
        TARGET chess-roguelike-cpp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets)


target_include_directories(chess-roguelike-cpp PUBLIC ${CMAKE_SOURCE_DIR}/external/FastNoiseLite)
# Link the engine library to the main app executable
target_link_libraries(chess-roguelike-cpp
        PRIVATE opengl-cpp-engine
        PRIVATE glad::glad
        PRIVATE glfw
        PRIVATE glm::glm-header-only
        PRIVATE OpenGL::GL)


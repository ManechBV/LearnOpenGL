cmake_minimum_required(VERSION 4.0.1)
project(game)

add_executable(${PROJECT_NAME} glad.c main.c)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(glfw)
target_link_libraries(${PROJECT_NAME} glfw)


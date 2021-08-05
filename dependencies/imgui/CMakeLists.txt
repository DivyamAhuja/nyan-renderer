cmake_minimum_required(VERSION 3.10)

project(imgui)

file(GLOB imgui_SRCS ${CMAKE_CURRENT_LIST_DIR}/imgui/*.cpp)
file(GLOB imgui_HDRS ${CMAKE_CURRENT_LIST_DIR}/imgui/*.h)

add_compile_definitions(
    IMGUI_IMPL_OPENGL_LOADER_GLAD
)

add_library(${PROJECT_NAME} ${imgui_SRCS} ${imgui_HDRS})

add_dependencies(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_dependencies(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
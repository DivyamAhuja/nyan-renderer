cmake_minimum_required(VERSION 3.10)

project(nyan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB C_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*.c")
file(GLOB CPP_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*.cpp")
file(GLOB H_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "src/*.h")
file(GLOB HPP_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "src/*.hpp")



add_executable(${PROJECT_NAME} ${C_SOURCES} ${CPP_SOURCES} ${H_HEADERS} ${HPP_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
#

# GLAD
add_subdirectory(dependencies/glad)
target_link_libraries(${PROJECT_NAME} glad)
#

# GLM
add_subdirectory(dependencies/glm)
target_link_libraries(${PROJECT_NAME} glm)
#

# STB
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/stb/include)
#

#
add_subdirectory(dependencies/imgui)
target_link_libraries(${PROJECT_NAME} imgui)
#

file(GLOB_RECURSE ASSETS RELATIVE ${PROJECT_SOURCE_DIR} "res/*")

foreach(ASSET ${ASSETS})
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/${ASSET} $<TARGET_FILE_DIR:${PROJECT_NAME}>/${ASSET}
)
endforeach()
#add_dependencies(${PROJECT_NAME} copy_assets)


# COPY RESOURCES
#file(GLOB_RECURSE ASSETS RELATIVE ${PROJECT_SOURCE_DIR} "res/*")
#
#foreach(ASSET ${ASSETS})
#    file(GENERATE OUTPUT ${ASSET} INPUT ${ASSET})
#endforeach(ASSET ${ASSETS})
#
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                       ${CMAKE_CURRENT_SOURCE_DIR}/res/
#                       $<TARGET_FILE_DIR:MyExe>
#                   )
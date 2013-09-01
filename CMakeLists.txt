cmake_minimum_required(VERSION 2.8)

project(luaSFML)
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
   add_definitions(-DLUA_USE_APICHECK)
endif()

file( GLOB_RECURSE SRC_LIST src/* game/*)

if(${BUILD_TYPE} STREQUAL "Lib")
	add_library(${PROJECT_NAME}  SHARED ${SRC_LIST})
	add_definitions(-DBUILD_LIB)
else()
	add_executable(${PROJECT_NAME} ${SRC_LIST})

endif()

target_link_libraries(${PROJECT_NAME} lua)
target_link_libraries(${PROJECT_NAME} sfml-system)
target_link_libraries(${PROJECT_NAME} sfml-window)
target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-audio)

#set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-save-temps")





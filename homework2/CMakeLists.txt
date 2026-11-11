cmake_minimum_required(VERSION 3.16)
project(fizkat_homework LANGUAGES CXX)

add_library(fizkat_core
    Inventory.cpp
    EnergyConsumer.cpp
    Transport.cpp
    Things.cpp
    ServiceCenter.cpp
    Fleet.cpp
    Commands.cpp
)
target_include_directories(fizkat_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(fizkat_core PUBLIC cxx_std_17)
set_target_properties(fizkat_core PROPERTIES CXX_EXTENSIONS OFF)

add_executable(fizkat main.cpp)
target_link_libraries(fizkat PRIVATE fizkat_core)
set_target_properties(fizkat PROPERTIES CXX_EXTENSIONS OFF)

if(MSVC)
  target_compile_options(fizkat_core PRIVATE /W4 /utf-8)
  target_compile_options(fizkat PRIVATE /W4 /utf-8)
else()
  target_compile_options(fizkat_core PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(fizkat PRIVATE -Wall -Wextra -Wpedantic)
endif()


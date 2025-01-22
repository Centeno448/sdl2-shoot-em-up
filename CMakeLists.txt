cmake_minimum_required(VERSION 3.5)

project(ShootEmUp VERSION 1.0)

if(WIN32)
    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
    find_package(SDL2_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL2_ttf)
    find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_ttf SDL2_image)
endif()

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

target_compile_options(compiler_flags INTERFACE
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
    "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)


add_executable(ShootEmUp)

target_include_directories(ShootEmUp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc "${SDL2_INCLUDE_DIRS}")

target_link_libraries(ShootEmUp PRIVATE compiler_flags)

if(WIN32)
  target_link_libraries(ShootEmUp PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
else()
  target_link_libraries(ShootEmUp PRIVATE ${SDL2_LIBRARIES})
endif()

target_sources(ShootEmUp 
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

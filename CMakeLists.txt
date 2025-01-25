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

add_executable(ShootEmUp WIN32)

set(GFX_PREFIX "/gfx")
set(GFX_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}${GFX_PREFIX}")

set(PLAYER_TEXTURE "${GFX_FOLDER}/player.png")
set(BULLET_TEXTURE "${GFX_FOLDER}/playerBullet.png")
set(ENEMY_TEXTURE "${GFX_FOLDER}/enemy.png")
set(ENEMY_BULLET_TEXTURE "${GFX_FOLDER}/enemyBullet.png")
set(BACKGROUND_TEXTURE "${GFX_FOLDER}/background.png")
set(EXPLOSION_TEXTURE "${GFX_FOLDER}/explosion.png")

set(SHOOTEMUP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")

configure_file("${SHOOTEMUP_INCLUDE_DIR}/defs.h.in" "${CMAKE_CURRENT_BINARY_DIR}/defs.h" @ONLY)

target_include_directories(ShootEmUp PRIVATE "${SHOOTEMUP_INCLUDE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" "${SDL2_INCLUDE_DIRS}")

target_link_libraries(ShootEmUp PRIVATE compiler_flags)

if(WIN32)
  target_link_libraries(ShootEmUp PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
else()
  target_link_libraries(ShootEmUp PRIVATE "${SDL2_LIBRARIES}")
endif()

target_sources(ShootEmUp
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/app.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/input_manager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/log.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sdl_wrappers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/texture_manager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/world.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/shootem_math.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/collision_manager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/timer_manager.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/entity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/bullet.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/player.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/enemy.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/enemy_bullet.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/effects/effect_manager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/effects/star.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/effects/background.cpp
)

if(WIN32)
add_custom_command(
    TARGET ShootEmUp POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE:SDL2_image::SDL2_image>" "$<TARGET_FILE:SDL2_ttf::SDL2_ttf>" "$<TARGET_FILE_DIR:ShootEmUp>"
    VERBATIM
    COMMENT "Copying SDL redistributables"
)
endif()

add_custom_command(
    TARGET ShootEmUp POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory_if_different "${GFX_FOLDER}" "$<TARGET_FILE_DIR:ShootEmUp>${GFX_PREFIX}"
    VERBATIM
    COMMENT "Copying Assets"
)

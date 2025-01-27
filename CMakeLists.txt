cmake_minimum_required(VERSION 3.5)

project(ShootEmUp VERSION 1.0)

if(WIN32)
    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
    find_package(SDL2_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL2_ttf)
    find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)
    find_package(SDL2_mixer REQUIRED CONFIG REQUIRED COMPONENTS SDL2_mixer)
    include(FetchContent)

    FetchContent_Declare(
      fmt
      GIT_REPOSITORY https://github.com/fmtlib/fmt
      GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
    FetchContent_MakeAvailable(fmt)
else()
    find_package(fmt REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_ttf SDL2_image SDL2_mixer)
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
set(FONT_TEXTURE "${GFX_FOLDER}/font.png")
set(POINTS_TEXTURE "${GFX_FOLDER}/points.png")

set(SFX_PREFIX "/sfx")
set(SFX_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}${SFX_PREFIX}")

set(PLAYER_SHOT_SFX "${SFX_FOLDER}/334227__jradcoolness__laser.ogg")
set(PLAYER_HIT_SFX "${SFX_FOLDER}/785800__alien_i_trust__pressure-kick-by-alien-i-trust-125_bpm-3.ogg")
set(PLAYER_DEATH_SFX "${SFX_FOLDER}/245372__quaker540__hq-explosion.ogg")
set(ENEMY_SHOT_SFX "${SFX_FOLDER}/196914__dpoggioli__laser-gun.ogg")
set(ENEMY_DEATH_SFX "${SFX_FOLDER}/10 Guage Shotgun-SoundBible.com-74120584.ogg")
set(POINTS_SFX "${SFX_FOLDER}/342749__rhodesmas__notification-01.ogg")
set(BACKGROUND_MUSIC_SFX "${SFX_FOLDER}/music/Mercury.ogg")

set(SHOOTEMUP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")

configure_file("${SHOOTEMUP_INCLUDE_DIR}/defs.h.in" "${CMAKE_CURRENT_BINARY_DIR}/defs.h" @ONLY)

target_include_directories(ShootEmUp PRIVATE "${SHOOTEMUP_INCLUDE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" "${SDL2_INCLUDE_DIRS}" "${FMT_INCLUDE_DIRS}")

target_link_libraries(ShootEmUp PRIVATE compiler_flags)

if(WIN32)
  target_link_libraries(ShootEmUp PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer fmt::fmt)
else()
  target_link_libraries(ShootEmUp PRIVATE "${SDL2_LIBRARIES}" fmt::fmt)
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
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sound_manager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hud.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/entity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/bullet.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/player.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/enemy.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/enemy_bullet.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/points.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/effects/effect_manager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/effects/star.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/effects/background.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/effects/explosion.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/effects/debris.cpp
)

if(WIN32)
add_custom_command(
    TARGET ShootEmUp POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE:SDL2_image::SDL2_image>" "$<TARGET_FILE:SDL2_ttf::SDL2_ttf>" "$<TARGET_FILE:SDL2_mixer::SDL2_mixer>" "$<TARGET_FILE:fmt::fmt>" "$<TARGET_FILE_DIR:ShootEmUp>"
    VERBATIM
    COMMENT "Copying SDL and fmt redistributables"
)
endif()

add_custom_command(
    TARGET ShootEmUp POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory_if_different "${GFX_FOLDER}" "$<TARGET_FILE_DIR:ShootEmUp>${GFX_PREFIX}"
    VERBATIM
    COMMENT "Copying GFX"
)

add_custom_command(
    TARGET ShootEmUp POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory_if_different "${SFX_FOLDER}" "$<TARGET_FILE_DIR:ShootEmUp>${SFX_PREFIX}"
    VERBATIM
    COMMENT "Copying SFX"
)

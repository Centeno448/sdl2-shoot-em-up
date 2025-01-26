#pragma once

#include <map>
#include <string>
#include <vector>

#include "sdl_wrappers.h"

enum SoundChannel { CH_ANY = -1, CH_PLAYER, CH_ENEMY };

struct Sound {
  Sound(std::string id, Mix_Chunk* sound) : id_(id) {
    sound_.reset(sound, &SDLMixChunkDeleter);
  };

  std::string id_;
  SDLMixChunkSharedPtr sound_;
};

class SoundManager {
  ~SoundManager() { Mix_CloseAudio(); }

 public:
  static void PlaySoundById(std::string id, SoundChannel channel);

  static void PlayMusic(std::string id);

  static void StaticInit();

 private:
  static SDLMixChunkSharedPtr LoadSoundById(std::string id);
  static SDLMixChunkSharedPtr GetSoundById(std::string id);

  inline static std::vector<Sound> loaded_sounds_ = {};

  static SDLMixMusicUniquePtr loaded_music_;

  static std::map<std::string, std::string> sound_map_;
};

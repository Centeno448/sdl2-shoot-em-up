#include "sound_manager.h"

#include <memory>

#include "defs.h"
#include "log.h"

void SoundManager::StaticInit() {
  LoadSoundById(BACKGROUND_MUSIC_SFX_ID);
  LoadSoundById(PLAYER_SHOT_SFX_ID);
  LoadSoundById(PLAYER_DEATH_SFX_ID);
  LoadSoundById(ENEMY_SHOT_SFX_ID);
  LoadSoundById(ENEMY_DEATH_SFX_ID);
}

SDLMixChunkSharedPtr SoundManager::LoadSoundById(std::string id) {
  std::string path = sound_map_.at(id);

  Log::Info(std::format("Loading sound {} with path {}", id, path));

  Mix_Chunk* t = Mix_LoadWAV(path.c_str());

  loaded_sounds_.emplace_back(id, t);

  return loaded_sounds_.back().sound_;
};

SDLMixChunkSharedPtr SoundManager::GetSoundById(std::string id) {
  auto found = std::find_if(loaded_sounds_.cbegin(), loaded_sounds_.cend(),
                            [&id](Sound sound) { return sound.id_ == id; });

  if (found != loaded_sounds_.cend()) {
    return found->sound_;
  }

  Log::Error(std::format("Failed to get sound {}. Sound not found", id));

  return nullptr;
}

void SoundManager::PlaySoundById(std::string id, SoundChannel channel) {
  SDLMixChunkSharedPtr sound = GetSoundById(id);

  if (!sound) {
    return;
  }

  Mix_PlayChannel(channel, sound.get(), 0);
}

void SoundManager::PlayMusic(std::string id) {
  std::string path = sound_map_.at(id);

  loaded_music_.reset(Mix_LoadMUS(path.c_str()));

  Mix_PlayMusic(loaded_music_.get(), -1);
}

std::map<std::string, std::string> SoundManager::sound_map_ = {
    {PLAYER_SHOT_SFX_ID, PLAYER_SHOT_SFX},
    {PLAYER_DEATH_SFX_ID, PLAYER_DEATH_SFX},
    {ENEMY_SHOT_SFX_ID, ENEMY_SHOT_SFX},
    {ENEMY_DEATH_SFX_ID, ENEMY_DEATH_SFX},
    {BACKGROUND_MUSIC_SFX_ID, BACKGROUND_MUSIC_SFX}};

SDLMixMusicUniquePtr SoundManager::loaded_music_ =
    SDLMixMusicUniquePtr(nullptr, &SDLMixMusicDeleter);

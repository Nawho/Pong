#pragma once

#include <SDL_mixer.h>
#include <string>
#include <unordered_map>

//Using singleton pattern for all managers

class AudioManager {
public:
    static AudioManager& getInstance();
    ~AudioManager();

    Mix_Chunk* loadAudio(const std::string& filename);
    void playAudio(Mix_Chunk* audio);
    void playAudio(Mix_Chunk* audio, int channel, int loops);

private:
    AudioManager();

    std::unordered_map<std::string, Mix_Chunk*> loadedAudios;
};
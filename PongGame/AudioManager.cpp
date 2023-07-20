#include "AudioManager.h"
#include "Constants.h"
#include <iostream>
#include <SDL_mixer.h>
#include <SDL.h>

AudioManager::AudioManager() {
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cerr << "ERROR: Audio initialization failed!" << std::endl;
        exit(-1);
    }

    int result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 1024);
    if (result != 0) {
        std::cout << "Failed to open audio: " << Mix_GetError() << std::endl;
        exit(-1);
    }

}
AudioManager::~AudioManager() {
    // Free all loaded audio resources on destruction
    /*for (auto& pair : loadedAudio) {
        Mix_FreeChunk(pair.second);
    }*/
    // Quit SDL_mixer here if needed
}

AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}


Mix_Chunk* AudioManager::loadAudio(const std::string& filename) {
    auto existingAudio = loadedAudios.find(filename);
    if (existingAudio != loadedAudios.end()) {
        return existingAudio->second; // second = value of the key-value pair stored in the iterator
    }

    std::string fullPath = Paths::AUDIO + filename;
    Mix_Chunk* audio = Mix_LoadWAV(fullPath.c_str());
    if (audio == nullptr) {
        std::cerr << "ERROR: Unable to load audio file: " << filename << std::endl;
        exit(-1);
    } else {
        loadedAudios[filename] = audio;
    }

    return audio;
}

void AudioManager::playAudio(Mix_Chunk* audio) {
    Mix_PlayChannel(-1, audio, 0);
}

void AudioManager::playAudio(Mix_Chunk* audio, int channel = -1, int loops = 0) {
    Mix_PlayChannel(channel, audio, loops);
}

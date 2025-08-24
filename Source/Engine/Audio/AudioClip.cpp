#include "EnginePCH.h"
#include "AudioClip.h"
#include "AudioSystem.h"

namespace Rex {

    AudioClip::~AudioClip() {

        if (s_sound) s_sound->release();
    }

    bool Rex::AudioClip::Load(const std::string& filename, AudioSystem& audioSystem) {

        
        FMOD_RESULT result = audioSystem.s_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &s_sound);
        if (!AudioSystem::CheckFMODResult(result)) return false;

        return true;
    }
}
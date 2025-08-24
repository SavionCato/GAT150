#include "AudioSystem.h"
#include "AudioClip.h"
#include "Core/Logger.h"
#include "../Core/StringHelper.h"

#include <fmod_errors.h>
#include <iostream>
#include <string>

namespace Rex {
	
	bool AudioSystem::CheckFMODResult(FMOD_RESULT result) {

		if (result != FMOD_OK) {

			Rex::Logger::Error(" ", std::string(FMOD_ErrorString(result)));
			return false;
		}

		return true;
	}

	bool AudioSystem::Initialize() {

		FMOD_RESULT result = FMOD::System_Create(&s_system);
		if (!CheckFMODResult(result)) return false;

		void* extradriverdata = nullptr;
		result = s_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result)) return false;

		return true;
	}
		
	void AudioSystem::Shutdown() {
		CheckFMODResult(s_system->release());
	}
		
	void AudioSystem::Update() {
		CheckFMODResult(s_system->update());
	}

	bool AudioSystem::AddSound(const std::string& filename, const std::string& name)
	{
		std::string key = (name.empty()) ? filename : name;
		key = tolower(key);

		if (s_sounds.find(key) != s_sounds.end()) {

			Rex::Logger::Error("Audio System : name already exists {}" , key);
			return false;
		}

		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = s_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!CheckFMODResult(result)) return false;

		s_sounds[key] = sound;

		return true;
	}

	bool AudioSystem::PlaySound(const std::string& name)
	{
		std::string key = name;
		key = tolower(key);

		// check if sound exists in sounds map
		if (s_sounds.find(key) == s_sounds.end()) {

			Rex::Logger::Error("Audio System : name doesn't exists {}" , key);
			return false;
		}

		// play sound from key
		FMOD_RESULT result = s_system->playSound(s_sounds[key], 0, false, nullptr);
		if (!CheckFMODResult(result)) return false;

		return true;
	}

	bool AudioSystem::PlaySound(AudioClip& audioClip) {

		FMOD_RESULT result = s_system->playSound(audioClip.s_sound, 0, false, nullptr);
		if (!CheckFMODResult(result)) return false;

		return true;
	}
}
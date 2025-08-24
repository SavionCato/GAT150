#pragma once
#include "Resources/Resource.h"

namespace Rex {
	class AudioClip : public Resource {
	public:

		AudioClip() = default;
		~AudioClip();

		bool Load(const std::string& filename, class AudioSystem& audioSystem);
	private:

		friend class AudioSystem;

		FMOD::Sound* s_sound{ nullptr };
	};
}
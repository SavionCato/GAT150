#pragma once
#include "Core/Time.h"
#include "Core/Singleton.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Resources/ResourceManager.h"

#include <memory>

namespace Rex {

	class Renderer;
	class AudioSystem;
	class InputSystem;
	class ParticleSystem;

	class Engine : Singleton<Engine> {
	public:

		static Engine& Instance() {

			static Engine instance;
			return instance;
		}

		bool Initialize();
		void Shutdown();

		void Update();
		void Draw();

		Renderer& GetRenderer() { return *s_renderer; }
		AudioSystem& GetAudio() { return *s_audio; }
		InputSystem& GetInput() { return *s_input; }
		ParticleSystem& GetPS() { return *s_particleSystem;  }

		Time& GetTime() { return s_time; }
	private:

		friend class Singleton;

		Engine() = default;

		Time s_time;

		std::unique_ptr<Renderer> s_renderer;
		std::unique_ptr<AudioSystem> s_audio;
		std::unique_ptr<InputSystem> s_input;
		std::unique_ptr<ParticleSystem> s_particleSystem;
	};

	inline Engine& GetEngine() { return Engine::Instance(); }
	inline Renderer& GetRenderer() { return GetEngine().GetRenderer(); }
}

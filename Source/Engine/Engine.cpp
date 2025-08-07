#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.h"

namespace Rex {

	bool Engine::Initialize() {

		s_renderer = std::make_unique<Rex::Renderer>();
		s_renderer->Initialize();
		s_renderer->CreateWindow("Please don't blow up", 1280, 1024);

		s_input = std::make_unique<Rex::InputSystem>();
		s_input->Initialize();

		s_audio = std::make_unique<Rex::AudioSystem>();
		s_audio->Initialize();

		s_particleSystem = std::make_unique<Rex::ParticleSystem>();
		s_particleSystem->Initialize(5000);

		return true;
	}

	void Engine::Shutdown() {
		s_particleSystem->Shutdown();
		s_audio->Shutdown();
		s_input->Shutdown();
		s_renderer->Shutdown();
	}

	void Engine::Update() {
		s_time.Tick();
		s_input->Update();
		s_audio->Update();
		s_particleSystem->Update(s_time.GetDeltaTime());
	}

	void Engine::Draw()
	{
		//
	}



}
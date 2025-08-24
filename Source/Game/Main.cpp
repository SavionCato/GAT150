#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Core/File.h"
#include "Engine.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {

    Rex::file::SetCurrentDirectory("Assets");
    
    Rex::GetEngine().Initialize();

    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    // initialize sounds
    /*Rex::GetEngine().GetAudio().AddSound("bass.wav", "bass");
    Rex::GetEngine().GetAudio().AddSound("snare.wav", "snare");
    Rex::GetEngine().GetAudio().AddSound("clap.wav", "clap");
    Rex::GetEngine().GetAudio().AddSound("close-hat.wav", "close-hat");
    Rex::GetEngine().GetAudio().AddSound("open-hat.wav", "open-hat");*/

    auto texture = Rex::Resources().Get<Rex::Texture>("Rosalina2.gif", Rex::GetRenderer());
    /*std::shared_ptr<Rex::Texture> texture = std::make_shared<Rex::Texture>();
    texture->load("Rosalina_by_Shigehisa_Nakaue.png", Rex::GetRenderer());*/

    // create stars
    std::vector<Rex::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(Rex::vec2{ Rex::random::getReal() * 1280 , Rex::random::getReal() * 1024 });
    }

    SDL_Event e;
    bool quit = false;

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        Rex::GetEngine().Update();
        game->Update(Rex::GetEngine().GetTime().GetDeltaTime());

        if (Rex::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // draw
        Rex::vec3 color{ 0, 0, 0 };
        Rex::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        Rex::GetEngine().GetRenderer().Clear();

        Rex::GetEngine().GetRenderer().DrawTexture(*texture.get(), 30, 30);
        game->Draw(Rex::GetEngine().GetRenderer());

        Rex::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    Rex::GetEngine().Shutdown();

    return 0;
}
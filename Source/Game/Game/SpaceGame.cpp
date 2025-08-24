#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Input/InputSystem.h"
#include "Engine.h"
#include "EnginePCH.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"
#include "Resources/ResourceManager.h"

#include <vector>

bool SpaceGame::Initialize() {

    s_scene = std::make_unique<Rex::Scene>(this);

    s_titleText = std::make_unique<Rex::Text>(Rex::Resources().Get<Rex::Font>("arcadeclassic.ttf", 85.0f));
    s_scoreText = std::make_unique<Rex::Text>(Rex::Resources().Get<Rex::Font>("arcadeclassic.ttf", 48.0f));
    s_livesText = std::make_unique<Rex::Text>(Rex::Resources().Get<Rex::Font>("arcadeclassic.ttf", 35.0f));
        
    return true;
}

void SpaceGame::Update(float dt) {

    switch (s_gameState) {

    case SpaceGame::GameState::Initialize:

        s_gameState = GameState::Title;
        break;

    case SpaceGame::GameState::Title:

        if (Rex::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {

            s_gameState = GameState::StartGame;
        }
        break;

    case SpaceGame::GameState::StartGame:

        s_score = 0;
        s_lives = 3;
        s_gameState = GameState::StartRound;
        break;

    case SpaceGame::GameState::StartRound: {

        s_scene->RemoveAllActors();

        // create player
        Rex::Transform transform{ Rex::vec2{ Rex::GetEngine().GetRenderer().GetWidth() * 0.5f, Rex::GetEngine().GetRenderer().GetHeight() * 0.5f }, 0, 0.5f };
        auto player = std::make_unique<Player>(transform);
        player->speed = 1500.0f;
        player->rotationRate = 180.0f;
        //player->damping = 1.5f;
        player->name = "player";
        player->tag = "player";

        auto spriteRenderer = std::make_unique<Rex::SpriteRenderer>();
        spriteRenderer->TextureName = "Rosalina.png";

        auto rb = std::make_unique<Rex::RigidBody>();
        rb->damping = 1.5f;

        auto collider = std::make_unique<Rex::CircleCollider2D>();
        collider->radius = 60;

        player->AddComponent(std::move(spriteRenderer));
        player->AddComponent(std::move(rb));
        player->AddComponent(std::move(collider));
        s_scene->AddActor(std::move(player));
        s_gameState = GameState::Game;
    }
        break;
    case SpaceGame::GameState::Game:

        s_enemySpawnTimer -= dt;
        if (s_enemySpawnTimer <= 0) {

            s_enemySpawnTimer = 2;
            SpawnEnemy();
        }

        break;
    case SpaceGame::GameState::PlayerDead:

        s_stateTimer -= dt;
        if (s_stateTimer <= 0) {

            s_lives--;
            if (s_lives == 0) {

                s_gameState = GameState::GameOver;
                s_stateTimer = 3;
            }else {

                s_gameState = GameState::StartRound;
            }
        }
        break;
    case SpaceGame::GameState::GameOver:

        s_stateTimer -= dt;
        if (s_stateTimer <= 0) {

            s_gameState = GameState::Title;
        }
        break;
    default:

        break;
    }

    if (Rex::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) {

        Rex::GetEngine().GetTime().SetTimeScale(0.15f);
    }else {

        Rex::GetEngine().GetTime().SetTimeScale(1.0f);
    }

    s_scene->Update(Rex::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(Rex::Renderer& renderer) {

    if (s_gameState == GameState::Title) {

        s_titleText->Create(renderer, "Galactic Corruption", Rex::vec3{ 1, 0, 0 });
        s_titleText->Draw(renderer, 200, 400);
    }
    if (s_gameState == GameState::GameOver) {

        s_titleText->Create(renderer, "GAME OVER", Rex::vec3{ 1, 0, 0 });
        s_titleText->Draw(renderer, 400, 400);
    }

    s_scoreText->Create(renderer, "SCORE  " + std::to_string(s_score), { 1, 1, 1 });
    s_scoreText->Draw(renderer, 20, 20);

    s_livesText->Create(renderer, "LIVES  " + std::to_string(s_lives), {1, 1, 1});
    s_livesText->Draw(renderer, (float)(renderer.GetWidth() - 200), (float)20);

    s_scene->Draw(renderer);

    Rex::GetEngine().GetPS().Draw(renderer);
}

void SpaceGame::OnPlayerDeath() {

    s_gameState = GameState::PlayerDead;
    s_stateTimer = 2;
}

void SpaceGame::SpawnEnemy() {

    Player* player = s_scene->GetActorByName<Player>("player");
    if (player) {

        // spawn at random position away from player
        Rex::vec2 position = player->transform.position + Rex::random::onUnitCircle() * Rex::random::getReal(200.0f, 500.0f);
        Rex::Transform transform{ position, Rex::random::getReal(0.0f, 360.0f), 0.1f};

        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform);
        //enemy->damping = 0.5f;
        enemy->fireTime = 3;
        enemy->fireTimer = 5;
        enemy->speed = (Rex::random::getReal() * 200) + 100;
        enemy->tag = "enemy";

        auto spriteRenderer = std::make_unique<Rex::SpriteRenderer>();
        spriteRenderer->TextureName = "Bowser.png";

        auto rb = std::make_unique<Rex::RigidBody>();
        rb->damping = 0.5f;

        auto collider = std::make_unique<Rex::CircleCollider2D>();
        collider->radius = 60;

        enemy->AddComponent(std::move(rb));
        enemy->AddComponent(std::move(spriteRenderer));
        enemy->AddComponent(std::move(collider));
        s_scene->AddActor(std::move(enemy));
    }
}

void SpaceGame::Shutdown() {
    //
}

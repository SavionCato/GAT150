#include "Player.h"
#include "Rocket.h"
#include "Engine.h"
#include "SpaceGame.h"
#include "GameData.h"
#include "Math/Vector3.h"
#include "Core/Random.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

void Player::Update(float dt)
{
    Rex::Particle particle;
    particle.position = transform.position;
    particle.velocity = Rex::vec2{ Rex::random::getReal(-200.0f, 200.0f), Rex::random::getReal(-200.0f, 200.0f) };
    particle.color = Rex::vec3{ 1, 1, 1 };
    particle.lifespan = 2;
    //Rex::GetEngine().GetPS().AddParticle(particle);

    // rotation
    float rotate = 0;
    if (Rex::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (Rex::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    transform.rotation += (rotate * rotationRate) * dt;

    // thrust
    float thrust = 0;
    if (Rex::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    if (Rex::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    Rex::vec2 direction{ 1, 0 };
    Rex::vec2 force = direction.Rotate(Rex::math::degToRad(transform.rotation)) * thrust * speed;
    velocity += force * dt;

    transform.position.x = Rex::math::wrap(transform.position.x, 0.0f, (float)Rex::GetEngine().GetRenderer().GetWidth());
    transform.position.y = Rex::math::wrap(transform.position.y, 0.0f, (float)Rex::GetEngine().GetRenderer().GetHeight());

    // check fire key pressed
    fireTimer -= dt;
    if (Rex::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
        fireTimer = fireTime;

        Rex::GetEngine().GetAudio().PlaySound("clap");

        std::shared_ptr<Rex::Model> model = std::make_shared<Rex::Model>(GameData::shipPoints, Rex::vec3{ 1.0f, 1.0f, 1.0f });
        // spawn rocket at player position and rotation
        Rex::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
        auto rocket = std::make_unique<Rocket>(transform, model);
        rocket->speed = 1500.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "rocket";
        rocket->tag = "player";

        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
    if (tag != other->tag) {
        destroyed = true;
        dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
    }
}


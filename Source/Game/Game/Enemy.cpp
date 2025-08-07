#include "Enemy.h"
#include "Engine.h"
#include "Core/Random.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/ParticleSystem.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

void Enemy::Update(float dt)
{
    bool playerSeen = false;

    Player* player = scene->GetActorByName<Player>("player");
    if (player) {
        Rex::vec2 direction{ 0, 0 };
        direction = player->transform.position - transform.position;

        direction = direction.Normalized();
        Rex::vec2 forward = Rex::vec2{ 1, 0 }.Rotate(Rex::math::degToRad(transform.rotation));

        float angle = Rex::math::radToDeg(Rex::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;

        if (playerSeen) {
            float angle = Rex::vec2::SignedAngleBetween(forward, direction);
            angle = Rex::math::sign(angle);
            transform.rotation += Rex::math::radToDeg(angle * 5 * dt);
        }
    }

    Rex::vec2 force = Rex::vec2{ 1, 0 }.Rotate(Rex::math::degToRad(transform.rotation)) * speed;
    velocity += force * dt;

    transform.position.x = Rex::math::wrap(transform.position.x, 0.0f, (float)Rex::GetEngine().GetRenderer().GetWidth());
    transform.position.y = Rex::math::wrap(transform.position.y, 0.0f, (float)Rex::GetEngine().GetRenderer().GetHeight());

    // check fire
    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;

        std::shared_ptr<Rex::Model> model = std::make_shared<Rex::Model>(GameData::shipPoints, Rex::vec3{ 0.0f, 1.0f, 0.0f });
        // spawn rocket at player position and rotation
        Rex::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
        auto rocket = std::make_unique<Rocket>(transform, model);
        rocket->speed = 500.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "rocket";
        rocket->tag = "enemy";

        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
    if (tag != other->tag) {
        destroyed = true;
        scene->GetGame()->AddPoints(100);
        for (int i = 0; i < 100; i++) {
            Rex::Particle particle;
            particle.position = transform.position;
            particle.velocity = Rex::random::onUnitCircle() * Rex::random::getReal(10.0f, 200.0f);
            particle.color = Rex::vec3{ 1, 1, 1 };
            particle.lifespan = 2;

            Rex::GetEngine().GetPS().AddParticle(particle);
        }
    }
}

#include "Rocket.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
#include "Player.h"

void Rocket::Update(float dt)
{
    Rex::vec2 force = Rex::vec2{ 1, 0 }.Rotate(Rex::math::degToRad(transform.rotation)) * speed;
    velocity = force;

    transform.position.x = Rex::math::wrap(transform.position.x, 0.0f, (float)Rex::GetEngine().GetRenderer().GetWidth());
    transform.position.y = Rex::math::wrap(transform.position.y, 0.0f, (float)Rex::GetEngine().GetRenderer().GetHeight());

    float angle = transform.rotation + Rex::random::getReal(-60.0f, 60.0f);
    Rex::vec2 velocity = Rex::vec2{ 1, 0 }.Rotate(Rex::math::degToRad(angle));
    velocity *= Rex::random::getReal(80.0f, 150.0f);

    Rex::Particle particle;
    particle.position = transform.position;
    particle.velocity = velocity;
    particle.color = (tag == "enemy") ? Rex::vec3{ 0, 1, 1 } : Rex::vec3{ 1, 1, 0 };
    particle.lifespan = Rex::random::getReal(0.15f, 0.3f);

    Rex::GetEngine().GetPS().AddParticle(particle);

    Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other)
{
    if (tag != other->tag) {
        destroyed = true;
    }
}

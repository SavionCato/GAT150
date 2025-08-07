#include "Actor.h"
#include "../Renderer/Model.h"

namespace Rex {
	void Actor::Update(float dt)
	{
		if (destroyed) return;

		if (lifespan != 0) {
			lifespan -= dt;
			destroyed = lifespan <= 0;
		}

		transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}

	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;

		s_model->Draw(renderer, transform);
	}

	float Actor::GetRadius()
	{
		return (s_model) ? s_model->GetRadius() * transform.scale * 0.9f : 0;
	}
}

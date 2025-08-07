#pragma once
#include "Framework/Actor.h"

class Rocket : public Rex::Actor {
public:
	float speed = 200;

public:
	Rocket() = default;
	Rocket(const Rex::Transform& transform, std::shared_ptr<Rex::Model> model) :
		Actor{ transform, model }
	{
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};

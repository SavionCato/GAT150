#pragma once
#include "Framework/Actor.h"

class Rocket : public Rex::Actor {
public:

	float speed = 200;

public:

	Rocket() = default;
	Rocket(const Rex::Transform& transform) :

		Actor{ transform}
	{}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};

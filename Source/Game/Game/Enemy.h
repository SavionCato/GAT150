#pragma once
#include "Framework/Actor.h"

class Enemy : public Rex::Actor {
public:

	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;
public:

	Enemy() = default;
	Enemy(const Rex::Transform& transform) :

		Actor{transform}
	{}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};

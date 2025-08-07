#pragma once
#include "Framework/Actor.h"

class Player : public Rex::Actor {
public:
	float speed = 200;
	float rotationRate = 180;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;

public:
	Player() = default;
	Player(const Rex::Transform& transform, std::shared_ptr<Rex::Model> model) :
		Actor{ transform, model }
	{}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};

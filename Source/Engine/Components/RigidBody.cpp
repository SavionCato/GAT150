#include "EnginePCH.h"
#include "RigidBody.h"

namespace Rex {

	void Rex::RigidBody::Update(float dt) {

		owner->transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}
}

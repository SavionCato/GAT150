#pragma once
#include "Framework/Component.h"

namespace Rex {
	class RigidBody : public Component {
	public:

		vec2 velocity;
		float damping{ 0 };

		void Update(float dt) override;
	};
}
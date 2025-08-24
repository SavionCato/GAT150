#pragma once
#include "Framework/Component.h"

namespace Rex {
	class ColliderComponent : public Component {
	public:

		virtual bool CheckCollider(ColliderComponent& other) = 0;
	};
}
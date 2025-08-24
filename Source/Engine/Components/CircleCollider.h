#pragma once
#include "Components/ColliderComponent.h"

namespace Rex {
	class CircleCollider2D : public ColliderComponent {
	public:

		float radius{ 0 };
				
		void Update(float dt) override;

		bool CheckCollider(ColliderComponent& other) override;
	};
}
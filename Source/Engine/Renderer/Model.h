#pragma once
#include "../Math/Vector3.h"
#include "../Math/Transform.h"
#include <vector>

namespace Rex {
	class Model {
	public:
		Model() = default;
		Model(const std::vector<vec2> points, const vec3& color) :
			s_points{ points },
			s_color{ color }
		{
			CalculateRadius();
		}

		void Draw(class Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(class Renderer& renderer, const Transform& transform);

		float GetRadius() const { return s_radius; }

	private:
		void CalculateRadius();

	private:
		float s_radius{ 0 };
		std::vector<vec2> s_points;
		vec3 s_color{ 1, 1, 1 };
	};
}
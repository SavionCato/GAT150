#pragma once
#include "../Math/Transform.h"
#include "Renderer/Texture.h"
#include <string>
#include <memory>

namespace Rex {
	class Actor {
	public:
		std::string name;
		std::string tag;

		vec2 velocity{ 0, 0 };
		float damping{ 0.0f };

		bool destroyed{ false };
		float lifespan{ 0 };


		Transform transform;
		class Scene* scene{ nullptr };

	public:
		Actor() = default;
		Actor(const Transform& transform, std::shared_ptr<class Model> model) :
			transform{ transform },
			s_model{ model }
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

	protected:

		res_t<Texture> s_texture;

		std::shared_ptr<Model> s_model;
	};
}
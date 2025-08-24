#pragma once
#include "../Math/Transform.h"
#include "Renderer/Texture.h"
#include "Object.h"
#include "Component.h"


#include <string>
#include <memory>

namespace Rex {
	class Actor : public Object {
	public:

		std::string tag;

		vec2 velocity{ 0, 0 };
		float damping{ 0.0f };

		bool destroyed{ false };
		float lifespan{ 0 };


		Transform transform;
		class Scene* scene{ nullptr };
	public:

		Actor() = default;
		Actor(const Transform& transform) :

			transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();
	protected:

		std::vector<std::unique_ptr<Component>> s_components;
		
	};

	template<typename T>
	inline T* Actor::GetComponent() {

		for (auto& component : s_components) {

			auto result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Actor::GetComponents() {


		std::vector<T*> results;
		for (auto& component : s_components) {

			auto result = dynamic_cast<T*>(component.get());
			if (result) results.push_back(result);
		}
		
		return;
	}
}
#include "Actor.h"
#include "../Renderer/Model.h"
#include "Components/RendererComponent.h"

namespace Rex {
	void Actor::Update(float dt) {

		if (destroyed) return;

		if (lifespan != 0) {
			lifespan -= dt;
			destroyed = lifespan <= 0;
		}

		for(auto& component : s_components){

			if (component->active) {

				component->Update(dt);
			}
		}
	}

	void Actor::Draw(Renderer& renderer) {

		if (destroyed) return;

		for (auto& component : s_components) {

			if (component->active) {

				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				
				if (rendererComponent) {

					rendererComponent->Draw(renderer);
				}				
			}
		}
	}

	float Actor::GetRadius() {

		return  50.0f;
	}

	void Actor::AddComponent(std::unique_ptr<class Component> component) {

		component->owner = this;
		s_components.push_back(std::move(component));
	}
}

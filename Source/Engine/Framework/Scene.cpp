#include "Scene.h"
#include "Actor.h"
#include "Components/CircleCollider.h"
#include "../Core/StringHelper.h"
#include "../Renderer/Renderer.h"

namespace Rex {
	
	void Scene::Update(float dt) {
		
		for (auto& actor : s_actors) {

			if (actor->active) {

				actor->Update(dt);
			}
		}

		for (auto iter = s_actors.begin(); iter != s_actors.end(); ) {

			if ((*iter)->destroyed) {

				iter = s_actors.erase(iter);
			}else {

				iter++;
			}
		}

		for (auto& actorA : s_actors) {

			for (auto& actorB : s_actors) {

				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

				auto colliderA = actorA->GetComponent<CircleCollider2D>();
				auto colliderB = actorB->GetComponent<CircleCollider2D>();

				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollider(*colliderB)) {

					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}

				float distance = (actorA->transform.position - actorB->transform.position).Length();
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {

					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}

	}

	void Scene::Draw(Renderer& renderer) {

		for (auto& actor : s_actors) {

			if (actor->active) {

				actor->Draw(renderer);
			}
		}
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		
		actor->scene = this;
		s_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors() {

		s_actors.clear();
	}
}
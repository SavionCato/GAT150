#pragma once
#include "../Core/StringHelper.h"

#include <string>
#include <vector>
#include <list>
#include <memory>

namespace Rex {

	class Actor;
	class Game;

	class Scene {
	public:

		Scene(Game* game) : s_game{ game } {}

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveAllActors();

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

		Game* GetGame() { return s_game; }
	private:

		Game* s_game{ nullptr };
		std::list<std::unique_ptr<Actor>> s_actors;
	};

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name) {

		for (auto& actor : s_actors) {

			if (Rex::tolower(actor->name) == Rex::tolower(name)) {

				T* object = dynamic_cast<T*>(actor.get());
				if (object) {

					return object;
				}
			}
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag) {

		std::vector<T*> results;
		for (auto& actor : s_actors) {

			if (Rex::tolower(actor->tag) == Rex::tolower(tag)) {

				T* object = dynamic_cast<T*>(actor.get());
				if (object) {

					results.push_back(object);
				}
			}
		}

		return results;
	}
}
#pragma once
#include <memory>

namespace Rex {
	class Game {
	public:
		Game() = default;

		virtual bool Initialize() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw(class Renderer& renderer) = 0;
		virtual void Shutdown() = 0;

		void AddPoints(int points) { s_score += points; }
		int GetPoints() const { return s_score; }

		void SetLives(int lives) { s_lives = lives; }
		int GetLives() const { return s_lives; }

	protected:
		int s_score{ 0 };
		int s_lives{ 0 };

		std::unique_ptr<class Scene> s_scene;
	};
}
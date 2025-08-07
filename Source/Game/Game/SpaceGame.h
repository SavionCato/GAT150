#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class SpaceGame : public Rex::Game {
public:

	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver,
	};

public:

	SpaceGame() = default;

	bool Initialize() override;
	void Shutdown() override;

	void Update(float dt) override;
	void Draw(class Rex::Renderer& renderer) override;

	void OnPlayerDeath();
private:

	void SpawnEnemy();
private:

	GameState s_gameState = GameState::Initialize;
	float s_enemySpawnTimer{ 0 };
	float s_stateTimer{ 0 };

	std::shared_ptr<class Rex::Font> s_titleFont;
	std::shared_ptr<class Rex::Font> s_uiFont;
	
	std::unique_ptr<class Rex::Text> s_titleText;
	std::unique_ptr<class Rex::Text> s_scoreText;
	std::unique_ptr<class Rex::Text> s_livesText;
};

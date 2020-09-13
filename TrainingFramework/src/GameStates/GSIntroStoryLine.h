#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class GSIntroStoryLine :
	public GameStateBase
{
public:
	GSIntroStoryLine();
	~GSIntroStoryLine();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_logo;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	float m_time;
};


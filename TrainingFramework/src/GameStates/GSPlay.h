#pragma once
#include "gamestatebase.h"

class Bullet;
class Enemy;
class Sprite2D;
class Sprite3D;
class Text;
class Character;
class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	
	void SetNewPostionForBullet();
	void Falling();

	float RandomFloat(float min, float max);
	int Randomint(int min, int max);

	void SpawnEnemy();
private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	
	std::vector<std::shared_ptr<Sprite2D>> m_ListBlock;
	std::vector<std::shared_ptr<Sprite2D>> m_ListCoin;
	std::vector<std::shared_ptr<Sprite2D>> m_ListBlockedBullet;
	std::vector<std::shared_ptr<Sprite2D>> m_ListDodge;
	std::vector<std::shared_ptr<Enemy>> m_ListEnemy;
	std::vector<std::shared_ptr<Bullet>> m_ListBullet;
	std::shared_ptr<Character>  m_Character;
	float m_horizontal;
	
	//std::shared_ptr<Character> m_playerCharacter;
};


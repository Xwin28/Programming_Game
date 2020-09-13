#pragma once
#include "gamestatebase.h"


class InteractOBJ;
class Bullet;
class Enemy;
class Sprite2D;
class Sprite3D;
class Text;
class Character;
class GSHome : public GameStateBase
{
public:
	GSHome::GSHome();


	GSHome::~GSHome();

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
	

	float RandomFloat(float min, float max);
	int Randomint(int min, int max);

	
private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_Coin;
	std::shared_ptr<Text>  m_BlockBullet;
	std::shared_ptr<Text>  m_Dodge;
	std::vector<std::shared_ptr<Sprite2D>> m_ListCoin;
	std::vector<std::shared_ptr<Sprite2D>> m_ListBlockedBullet;
	std::vector<std::shared_ptr<Sprite2D>> m_ListDodge;
	std::vector<std::shared_ptr<Enemy>> m_ListEnemy;
	std::vector<std::shared_ptr<Bullet>> m_ListBullet;
	std::vector<std::shared_ptr<Sprite2D>> m_ListBlock;
	std::shared_ptr<Character>  m_Character;
	std::shared_ptr<InteractOBJ>  m_PlusHeal;
	std::shared_ptr<InteractOBJ>  m_PlusDamage;
	std::shared_ptr<InteractOBJ>  m_Gate;
	float m_horizontal;
	int m_interactMode;

	//std::shared_ptr<Character> m_playerCharacter;
};


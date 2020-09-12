#pragma once
#include <string>
#include "Sprite2D.h"
#include "AnimationSprite2D.h"
#include "Enemy.h"
class Character: public AnimationSprite2D
{
protected:
	float m_Speed;
	float m_heal;
	float m_jumpHeight;
	float m_coin;
	int m_numberDodge;
	int m_numBlock;

	bool m_isJump;//Check Jump
	bool m_onGround;//Check Falling
	bool m_Atk;//Check ATk
	bool m_Hurt;//Check ATk
	bool m_Death;//Check ATk
	float _yPos;
	float _xPos;
	float m_horizotal;
	std::string m_animNow;
	float m_time;//CouDown Time
	float m_timeHurt;//CouDown Time

	//Animation
	std::shared_ptr<Texture>	m_animIdle, m_animIRun, m_animIFall, m_animIJump, m_animIATK, m_animIDeath, m_animIDodge, m_animIHurt;

public:
	Character();

	Character(float _speed, float _heal, int _numDodge, int _numBlock, float m_jumpHeight,
		std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime
	);
	~Character();
	void SetTexture(std::string _mode);
	int GetnBlock();
	bool GetATK();

	void Init() override;
	virtual void Update(GLfloat deltatime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock);
	void Draw() override;

	virtual void Falling(float _deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock);
	virtual void Moving(float _horizontal, GLfloat deltatime, std::vector<std::shared_ptr<Sprite2D>> &m_ListCoin,
						std::vector<std::shared_ptr<Sprite2D>> &m_ListBlockBullet,
						std::vector<std::shared_ptr<Sprite2D>> &m_ListDodge);
	virtual void ATK(std::vector<std::shared_ptr<Enemy>>& m_ListEnemy, std::vector<std::shared_ptr<Sprite2D>>& m_ListVFX);
	virtual void Dodge();
	virtual void Jump();
	void Hurt(int damage);
	void Death();

};
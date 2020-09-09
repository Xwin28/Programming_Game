#pragma once
#include <string>
#include "Sprite2D.h"
#include "AnimationSprite2D.h"

class Enemy : public AnimationSprite2D
{
private:

	float m_Speed;
	float m_heal;
	float m_jumpHeight;
	float m_coin;
	int m_numberDodge;
	int m_numBlock;

	bool m_isJump;//Check Jump
	bool m_onGround;//Check Falling
	bool m_Atk;//Check ATk
	float _yPos;
	float _xPos;
	float m_horizotal;
	std::string m_animNow;

	//Animation
	std::shared_ptr<Texture>	m_animIdle, m_animIRun, m_animIFall, m_animIJump, m_animIATK, m_animIDeath, m_animIDodge;

	int m_nIdle, m_nRun, m_nFall, m_nDeath, m_nAtk;
	bool doOne;
public:
	Enemy();

	Enemy(float _speed, float _heal, int _numDodge, int _numBlock, float m_jumpHeight,
		std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime,
		std::shared_ptr<Texture> _Idle, std::shared_ptr<Texture> _Run, std::shared_ptr<Texture> Fall, std::shared_ptr<Texture> _Death, std::shared_ptr<Texture> _ATK
		,int _nIdle, int _nRun, int _nFall, int _nDeath, int _nAtk
	);
	~Enemy();
	void SetTexture(std::string _mode);

	void Dead();

	void Init();
	void Update(GLfloat deltatime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock);
	void Draw();

	void Falling(float _deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock);
	void Moving(float _horizontal, GLfloat deltatime);
	void ATk();
	void Dodge();
	void Jump();

};
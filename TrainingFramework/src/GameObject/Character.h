#pragma once
#include <string>
#include "Sprite2D.h"
#include "AnimationSprite2D.h"
class Character: public AnimationSprite2D
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
	float _yPos;
	float _xPos;
	float m_horizotal;
	std::string m_animNow;

	//Animation
	std::shared_ptr<Texture>	m_animIdle, m_animIRun, m_animIFall, m_animIJump;
public:
	Character();

	Character(float _speed, float _heal, int _numDodge, int _numBlock, float m_jumpHeight,
		std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime
	);
	~Character();
	void SetTexture(std::string _mode);



	void Init();
	void Update(GLfloat deltatime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock);
	void Draw();

	void Falling(float _deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock);
	void Moving(float _horizontal, GLfloat deltatime);
	void ATk();
	void Dodge();
	void Jump();

};
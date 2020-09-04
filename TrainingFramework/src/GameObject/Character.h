#pragma once

#include "Sprite2D.h"
#include "AnimationSprite2D.h"
class Character: public AnimationSprite2D
{
private:
	float m_Speed;
	float m_heal;
	int m_numberDodge;
	int m_numBlock;
public:
	Character();

	Character(float _speed, float _heal, int _numDodge, int _numBlock,
		std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime
	);
	~Character();

	void Init();
	void Update(GLfloat deltatime);
	void Draw();

	void Falling(float _deltaTime);
	void Moving();
	void ATk();
	void Dodge();

};
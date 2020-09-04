#include "Character.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "AnimationSprite2D.h"
#include <iostream>



Character::Character(){}
Character::Character(float _speed, float _heal, int _numDodge, int _numBlock,
					std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime)
	:m_Speed(_speed), m_heal(_heal), m_numberDodge(_numDodge), m_numBlock(_numBlock), AnimationSprite2D(model, shader, texture, _numFrame, _frameTime)
{

}
Character::~Character(){}



void  Character::Init( )
{
	AnimationSprite2D::Init();
;
}


void Character::Falling(float _deltaTime)
{
	Vector2 _posTemp = Get2DPosition();
	if (_posTemp.y <= 700)
	{

		Set2DPosition(_posTemp.x, _posTemp.y + 400* _deltaTime);
	}
}


void Character::Moving()
{

}
void Character::ATk()
{
}
void Character::Dodge()
{
}
void Character::Update(GLfloat deltatime)
{
	AnimationSprite2D::Update(deltatime);
	Falling(deltatime);
	
}
void Character::Draw()
{
	AnimationSprite2D::Draw();
}
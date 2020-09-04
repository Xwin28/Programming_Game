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
#include <math.h>

Character::Character(){}
Character::Character(float _speed, float _heal, int _numDodge, int _numBlock,float _jumpHeight,
					std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime)
	:m_Speed(_speed), m_heal(_heal), m_numberDodge(_numDodge), m_numBlock(_numBlock), m_jumpHeight(_jumpHeight), AnimationSprite2D(model, shader, texture, _numFrame, _frameTime)
{
	m_isJump = true;
	m_onGround = false;

	m_horizotal=1;
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
	if (_posTemp.y <= 700 && m_isJump)
	{

		Set2DPosition(_posTemp.x, _posTemp.y + 400* _deltaTime);
		m_onGround = false;
		//std::cout << "\n Falling on Ground = " << m_onGround;
	}
	else
	{
		
		m_onGround = true;
		//std::cout << "\n Falling on Ground = " << m_onGround;
	}
}

void Character::Jump()
{
	if (m_onGround)
	{
		m_isJump = false;
		_yPos = Get2DPosition().y;

	}



}
void Character::Moving(float _horizontal,GLfloat deltatime)
{

	if (_horizontal != 0)
	{
		
		m_horizotal = _horizontal;
		std::cout<< " ,,, horizontal = " << m_horizotal;
		Set2DPosition(Get2DPosition().x + m_Speed * _horizontal * deltatime, Get2DPosition().y);
		
	}



}
void Character::ATk()
{
}
void Character::Dodge()
{

		m_dodge = true;
		Set2DPosition(Get2DPosition().x + m_horizotal * 50, Get2DPosition().y);
		std::cout << "\n Position = " << Get2DPosition().x<<" , horizontal = " <<m_horizotal;


}
void Character::Update(GLfloat deltaTime)
{
	AnimationSprite2D::Update(deltaTime);
	Falling(deltaTime);

	//Jump
	if (!m_isJump && m_onGround)
	{
		//std::cout << "\n on Ground in Updates = " << m_onGround;
		Set2DPosition(Get2DPosition().x, Get2DPosition().y - 500 * deltaTime);
		if (abs(Get2DPosition().y - _yPos) >= m_jumpHeight )
		{
			m_isJump = true;
			//m_onGround = false;
		}
	}
}
void Character::Draw()
{
	AnimationSprite2D::Draw();
}
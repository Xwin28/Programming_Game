
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
#include <string>
#include "GameManager/ResourceManagers.h"
#include "Enemy.h"

Enemy::Enemy() {}
Enemy::Enemy(float _speed, float _heal, int _numDodge, int _numBlock, float _jumpHeight,
	std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime,
	std::shared_ptr<Texture> _Idle, std::shared_ptr<Texture> _Run, std::shared_ptr<Texture> _Fall, std::shared_ptr<Texture> _Death, std::shared_ptr<Texture> _ATK,
	int _nIdle, int _nRun, int _nFall, int _nDeath, int _nAtk)
	:m_Speed(_speed), m_heal(_heal), m_numberDodge(_numDodge), m_numBlock(_numBlock), m_jumpHeight(_jumpHeight), AnimationSprite2D(model, shader, texture, _numFrame, _frameTime)
{
	m_nIdle = _nIdle;
	m_nRun = _nRun;
	m_nFall = _nFall;
	m_nDeath = _nDeath;
	m_nAtk = _nAtk;
	// use menory instead processing
	m_animIdle = _Idle;
	m_animIRun = _Run;
	m_animIFall = _Fall;
	m_animIATK = _ATK;

	doOne = false;
}
Enemy::~Enemy() {}



void  Enemy::Init()
{
	AnimationSprite2D::Init();
}


void Enemy::SetTexture(std::string _mode)// CALL THIS IN FUNCTION RUN, FALL...
{
	//_Idle, _Run, _Fall, _Death, _Atk
	if (m_animNow != _mode)// limit update
	{
		m_animNow = _mode;

		if (_mode == "Idle" && m_horizotal == 0)
		{
			m_numFrame = m_nIdle;
			m_pTexture = m_animIdle;
		}
		else if (_mode == "Run")
		{

			m_numFrame = m_nRun;
			m_pTexture = m_animIRun;
		}
		else if (_mode == "Atk")
		{
			m_numFrame = m_nAtk;
		}
		else if (_mode == "Dodge")
		{
			
		}
		else if (_mode == "Falling")
		{
			m_currentFrame = 0;
			m_numFrame = m_nFall;
			m_pTexture = m_animIFall;

		}
		else if (_mode == "Jump")
		{
			m_currentFrame = 0;
			m_numFrame = 1;
			m_pTexture = m_animIJump;

		}
		else if (_mode == "Death")
		{
			m_currentFrame = 0;
			m_numFrame = m_nDeath;
			m_pTexture = m_animIJump;

		}
		else
		{
			
			//m_currentFrame = 0;
			m_numFrame = m_nIdle;
			m_pTexture = m_animIdle;
		}

	}
	//Init();
}


void Enemy::Dead()
{
	 
}
void Enemy::Falling(float _deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock)
{
	//(x > m_Vec2DPos.x  - m_iWidth/2) && (x < m_Vec2DPos.x + m_iWidth / 2) && 
	//(y > m_Vec2DPos.y - m_iHeight / 2) && (y < m_Vec2DPos.y + m_iHeight / 2))

	Vector2 _BlockPos = m_ListBlock.front()->Get2DPosition();
	Vector2 _BlockSize = m_ListBlock.front()->GetSize();
	std::vector<std::shared_ptr<Sprite2D>> _Temp_ListBlock;
	_Temp_ListBlock.clear();
	for (auto obj : m_ListBlock)
	{
		if (Get2DPosition().y < obj->Get2DPosition().y)
		{
			_Temp_ListBlock.push_back(obj);
		}
	}


	for (auto obj : _Temp_ListBlock)
	{

		if (obj->Get2DPosition().y < _BlockPos.y)
		{

			_BlockPos = obj->Get2DPosition();
			_BlockSize = obj->GetSize();

		}

	}



	if ((Get2DPosition().x > _BlockPos.x - _BlockSize.x / 2) && (Get2DPosition().x < _BlockPos.x + _BlockSize.x / 2)
		&& (Get2DPosition().y >= _BlockPos.y - _BlockSize.y / 1.5) && (Get2DPosition().y <= _BlockPos.y + _BlockSize.y / 1.5)
		&& m_isJump)
	{
		Set2DPosition(Get2DPosition().x, _BlockPos.y - _BlockSize.y/1.55);
		m_onGround = true;
		SetTexture("Idle");
	}
	else if (m_isJump)
	{
		Set2DPosition(Get2DPosition().x, Get2DPosition().y + 400 * _deltaTime);
		m_onGround = false;
		SetTexture("Falling");

	}



}
void Enemy::Jump()
{
	if (m_onGround)
	{
		//std::cout << "\n Start JUMPING";
		m_isJump = false;
		_yPos = Get2DPosition().y;
		SetTexture("Jump");
	}
}
void Enemy::Moving(float _horizontal, GLfloat deltatime)
{
	if (_horizontal != 0 && !m_Atk)
	{

		if (_horizontal == -1 && _horizontal != m_horizotal)// do not run if already turn
		{

			FlipY(-1.0f);
		}
		else if (_horizontal == 1 && _horizontal != m_horizotal)// do not run if already turn
		{
			FlipY(1.0f);
		}
		m_horizotal = _horizontal;
		//std::cout<< " ,,, horizontal = " << m_horizotal;
		Set2DPosition(Get2DPosition().x + m_Speed * _horizontal * deltatime, Get2DPosition().y);
		if (m_onGround)
		{
			SetTexture("Run");
		}

	}
}
void Enemy::ATk()
{
}
void Enemy::Dodge()
{
	Set2DPosition(Get2DPosition().x + m_horizotal * 50, Get2DPosition().y);
	//std::cout << "\n Position = " << Get2DPosition().x<<" , horizontal = " <<m_horizotal;
}
void Enemy::Update(GLfloat deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock)
{
	
	AnimationSprite2D::Update(deltaTime);
	Falling(deltaTime, m_ListBlock);

	//Jump
	if (!m_isJump && m_onGround)
	{
		//std::cout << "\n on Ground in Updates = " << m_onGround;
		Set2DPosition(Get2DPosition().x, Get2DPosition().y - 500 * deltaTime);

		if (abs(Get2DPosition().y - _yPos) >= m_jumpHeight)
		{
			m_isJump = true;

		}
	}
}
void Enemy::Draw()
{
	AnimationSprite2D::Draw();
}
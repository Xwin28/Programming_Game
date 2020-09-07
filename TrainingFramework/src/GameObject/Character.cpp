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
#include <string>
#include "GameManager/ResourceManagers.h"


Character::Character(){}
Character::Character(float _speed, float _heal, int _numDodge, int _numBlock,float _jumpHeight,
					std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime)
	:m_Speed(_speed), m_heal(_heal), m_numberDodge(_numDodge), m_numBlock(_numBlock), m_jumpHeight(_jumpHeight), AnimationSprite2D(model, shader, texture, _numFrame, _frameTime)
{
	m_isJump = true;
	m_onGround = false;

	m_horizotal=1;
	m_animNow = "Idle";

	// use menory instead processing
	m_animIdle = ResourceManagers::GetInstance()->GetTexture("Character//Player//Idle");
	m_animIRun = ResourceManagers::GetInstance()->GetTexture("Character//Player//Run");
	m_animIFall = ResourceManagers::GetInstance()->GetTexture("Character//Player//Fall");
	m_animIJump = ResourceManagers::GetInstance()->GetTexture("Character//Player//Jump");
}
Character::~Character(){}



void  Character::Init( )
{
	AnimationSprite2D::Init();
;
}


void Character::SetTexture(std::string _mode)// CALL THIS IN FUNCTION RUN, FALL...
{

	if (m_animNow != _mode)// limit update
	{
		m_animNow = _mode;

	if (_mode == "Idle" && m_horizotal == 0)
	{
		//std::cout << "\n IDLE Animation"<<" , Location x = "<<Get2DPosition().x;
		//m_currentFrame = 0;
		m_numFrame = 8;
		m_pTexture = m_animIdle;
	}
	else if (_mode == "Run")
	{
		//std::cout << "\n Run Animation";
		//m_currentFrame = 0;
		m_numFrame = 8;
		m_pTexture = m_animIRun;
	}
	else if (_mode == "Atk")
	{
		std::cout << "\n Atk Animation";
		//m_pTexture = ResourceManagers::GetInstance()->GetTexture("Character//Player//Attack1");
	}
	else if (_mode == "Dodge")
	{
		std::cout << "\n Dodge Animation";
		//m_pTexture = ResourceManagers::GetInstance()->GetTexture("Character//Player//Idle");
	}
	else if (_mode == "Falling")
	{
		//std::cout << "\n Falling Animation" << " , Location y = " << Get2DPosition().y;
		m_currentFrame = 0;
		m_numFrame = 2;
		m_pTexture = m_animIFall;
		
	}
	else if (_mode == "Jump")
	{
		//std::cout << "\n Jump Animation" << " , Location y = " << Get2DPosition().y;
		m_currentFrame = 0;
		m_numFrame = 2;
		m_pTexture = m_animIJump;
		
	}
	else
	{
		//m_currentFrame = 0;
		m_numFrame = 8;
		m_pTexture = m_animIdle;
	}

	}
	//Init();
}



void Character::Falling(float _deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock)
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
			std::cout << "\n BlockPos == " << _BlockPos.y;
		}
		else
		{
			std::cout << "\n BlockPos Not Change == " << _BlockPos.y;
		}
	}



		if ((Get2DPosition().x > _BlockPos.x - _BlockSize.x / 2) && (Get2DPosition().x < _BlockPos.x + _BlockSize.x / 2)
			&& (Get2DPosition().y >= _BlockPos.y - _BlockSize.y / 1.2) && (Get2DPosition().y <= _BlockPos.y + _BlockSize.y / 1.2)
			&& m_isJump)
		{
			std::cout << "\nOnGround" << " Pos_y = " << Get2DPosition().y << " Block_y = " << _BlockPos.y - _BlockSize.x / 1;
			m_onGround = true;
			//std::cout << "\n\n onGround = "<<m_onGround <<"  ; Pos y = "<<Get2DPosition().y;
			SetTexture("Idle");
			//std::cout << "\n Falling on Ground = " << m_onGround;
		}
		else if (/*(Get2DPosition().x > obj->Get2DPosition().x - obj->GetSize().x / 2) && (Get2DPosition().x < obj->Get2DPosition().x + obj->GetSize().x / 2)
			&& (Get2DPosition().y > obj->Get2DPosition().y - obj->GetSize().x / 2) && (Get2DPosition().y < obj->Get2DPosition().y + obj->GetSize().x / 2)*/
			 m_isJump)
		{
			std::cout << "\nFalling" << " Pos_y = " << Get2DPosition().y << " Block_y = " << _BlockPos.y - _BlockSize.x / 2;
			Set2DPosition(Get2DPosition().x, Get2DPosition().y + 400 * _deltaTime);
			m_onGround = false;
			SetTexture("Falling");
			//std::cout << "\n Falling on Ground = " << m_onGround;
		}
		else
		{
			std::cout<<"\nFAIL " << " Pos_y = " << Get2DPosition().y << " Block_y = " << _BlockPos.y - _BlockSize.x / 2;
		}



	//if (Get2DPosition().y <= 700 && m_isJump)
	//{

	//	Set2DPosition(Get2DPosition().x, Get2DPosition().y + 400* _deltaTime);
	//	m_onGround = false;
	//	SetTexture("Falling");
	//	//std::cout << "\n Falling on Ground = " << m_onGround;
	//}
	//else if(Get2DPosition().y > 700 && m_isJump)
	//{
	//	m_onGround = true;
	//	//std::cout << "\n\n onGround = "<<m_onGround <<"  ; Pos y = "<<Get2DPosition().y;
	//	SetTexture("Idle");
	//	//std::cout << "\n Falling on Ground = " << m_onGround;
	//}
}
void Character::Jump()
{
	if (m_onGround)
	{
		//std::cout << "\n Start JUMPING";
		m_isJump = false;
		_yPos = Get2DPosition().y;
		SetTexture("Jump");
	}

}
void Character::Moving(float _horizontal,GLfloat deltatime)
{

	if (_horizontal != 0)
	{
		std::cout << " \n ROTATION Y = :" << m_Vec3Rotation.y;
		std::cout <<"Location  ,x = " << Get2DPosition().x;
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
void Character::ATk()
{
}
void Character::Dodge()
{

		Set2DPosition(Get2DPosition().x + m_horizotal * 50, Get2DPosition().y);
		std::cout << "\n Position = " << Get2DPosition().x<<" , horizontal = " <<m_horizotal;

}
void Character::Update(GLfloat deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock)
{
	AnimationSprite2D::Update(deltaTime);
	Falling(deltaTime, m_ListBlock);

	//Jump
	if (!m_isJump && m_onGround)
	{
		//std::cout << "\n on Ground in Updates = " << m_onGround;
		Set2DPosition(Get2DPosition().x, Get2DPosition().y - 500 * deltaTime);
		
		if (abs(Get2DPosition().y - _yPos) >= m_jumpHeight )
		{
			m_isJump = true;
			
		}
	}
}
void Character::Draw()
{
	AnimationSprite2D::Draw();
}
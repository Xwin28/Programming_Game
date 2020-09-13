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
#include <vector>
#include "VFX.h"

Character::Character(){}
Character::Character(float _speed, float _heal, int _numDodge, int _numBlock,float _jumpHeight,
					std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime)
	:m_Speed(_speed), m_heal(_heal), m_numberDodge(_numDodge), m_numBlock(_numBlock), m_jumpHeight(_jumpHeight), AnimationSprite2D(model, shader, texture, _numFrame, _frameTime)
{
	m_isJump = true;
	m_onGround = false;
	m_Atk = false;
	m_Hurt = false;
	m_Death = false;
	m_CanATK = true;
	m_coin=0;
	m_numberDodge=0;
	m_numBlock=0;

	m_horizotal=1;
	m_animNow = "Idle";
	m_time = 0;
	m_timeHurt = 0;
	m_timeCanATK = 0;
	// use menory instead processing
	m_animIdle = ResourceManagers::GetInstance()->GetTexture("Character//Player//Idle");
	m_animIRun = ResourceManagers::GetInstance()->GetTexture("Character//Player//Run");
	m_animIFall = ResourceManagers::GetInstance()->GetTexture("Character//Player//Fall");
	m_animIJump = ResourceManagers::GetInstance()->GetTexture("Character//Player//Jump");
	m_animIDeath = ResourceManagers::GetInstance()->GetTexture("Character//Player//Death");
	m_animIDodge = ResourceManagers::GetInstance()->GetTexture("Character//Player//Take Hit");
	m_animIATK = ResourceManagers::GetInstance()->GetTexture("Character//Player//Attack");
	m_animIHurt = ResourceManagers::GetInstance()->GetTexture("Character//Player//Take Hit");
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

		m_currentFrame = 0;
		m_numFrame = 3;
		m_pTexture = m_animIATK;
	}
	else if (_mode == "Dodge")
	{

		m_pTexture = m_animIDodge;
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
	else if (_mode == "Death")
	{
		m_currentFrame = 0;
		m_numFrame = 1;
		m_pTexture = m_animIDeath;

	}
	else if (_mode == "Hurt")
	{

		m_currentFrame = 0;
		m_numFrame = 4;
		m_pTexture = m_animIHurt;
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
int Character::GetnBlock()
{
	return m_numBlock;
}
bool Character::GetATK()
{
	return m_Atk;
}
float  Character::GetHorizontal()
{
	return m_horizotal;
}
void Character::Falling(float _deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock)
{
	//(x > m_Vec2DPos.x  - m_iWidth/2) && (x < m_Vec2DPos.x + m_iWidth / 2) && 
	//(y > m_Vec2DPos.y - m_iHeight / 2) && (y < m_Vec2DPos.y + m_iHeight / 2))
	if (!m_Atk && !m_Hurt)
	{

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
			&& (Get2DPosition().y >= _BlockPos.y - _BlockSize.y / 0.9) && (Get2DPosition().y <= _BlockPos.y + _BlockSize.y / 0.9)
			&& m_isJump)
		{
			Set2DPosition(Get2DPosition().x, _BlockPos.y - _BlockSize.y / 1);
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
}
void Character::Jump()
{
	if (m_onGround && m_isJump)
	{
		//std::cout << "\n Start JUMPING";
		m_isJump = false;
		_yPos = Get2DPosition().y;
		SetTexture("Jump");
	}

}
void Character::Moving(float _horizontal,GLfloat deltatime, 
						std::vector<std::shared_ptr<Sprite2D>> &m_ListCoin, 
						std::vector<std::shared_ptr<Sprite2D>> &m_ListBlockBullet,
						std::vector<std::shared_ptr<Sprite2D>> &m_ListDodge)
{

	if (_horizontal != 0 && !m_Atk && !m_Hurt)
	{

		if (_horizontal == -1 && _horizontal != m_horizotal)// do not run if already turn
		{
			
			FlipY(-1.0f);
		}
		else if (_horizontal == 1 && _horizontal != m_horizotal)// do not run if already turn
		{
			FlipY(1.0f);
		}

#pragma region TakeCoin
		std::vector<int> _ListIndex;
		_ListIndex.clear();
		int _IndexInListE = 0;
		for (auto obj : m_ListCoin)
		{
			Vector2 _EPos = obj->Get2DPosition();
			Vector2 _ESize = obj->GetSize();
			if ((Get2DPosition().x > _EPos.x - _ESize.x / 2) && (Get2DPosition().x < _EPos.x + _ESize.x / 2)
				&& (Get2DPosition().y >= _EPos.y - _ESize.y / 2) && (Get2DPosition().y <= _EPos.y + _ESize.y / 2))
			{

				//m_ListEnemy.erase(m_ListEnemy.begin());
				_ListIndex.push_back(_IndexInListE);
				
			}
			_IndexInListE++;
		}

		for (auto obj_index : _ListIndex)
		{
			_IndexInListE = 0;
			for (auto obj_E : m_ListCoin)
			{
				if (_IndexInListE == obj_index)
				{
					m_ListCoin.erase(m_ListCoin.begin() + _IndexInListE);
					m_coin++;
					std::cout << "\n Take COIN = " << m_coin;
				}
				_IndexInListE++;
			}

		}
	
#pragma endregion
#pragma region TakeBlockBulet
	_ListIndex.clear();
	_IndexInListE = 0;
	for (auto obj : m_ListBlockBullet)
	{
		Vector2 _EPos = obj->Get2DPosition();
		Vector2 _ESize = obj->GetSize();
		if ((Get2DPosition().x > _EPos.x - _ESize.x / 2) && (Get2DPosition().x < _EPos.x + _ESize.x / 2)
			&& (Get2DPosition().y >= _EPos.y - _ESize.y / 2) && (Get2DPosition().y <= _EPos.y + _ESize.y / 2))
		{

			//m_ListEnemy.erase(m_ListEnemy.begin());
			_ListIndex.push_back(_IndexInListE);

		}
		_IndexInListE++;
	}

	for (auto obj_index : _ListIndex)
	{
		_IndexInListE = 0;
		for (auto obj_E : m_ListBlockBullet)
		{
			if (_IndexInListE == obj_index)
			{
				m_ListBlockBullet.erase(m_ListBlockBullet.begin() + _IndexInListE);
				m_numBlock++;
				std::cout << "\n Take Block = " << m_numBlock++;
			}
			_IndexInListE++;
		}

	}

#pragma endregion
#pragma region TakeDodge
	_ListIndex.clear();
	_IndexInListE = 0;
	for (auto obj : m_ListDodge)
	{
		Vector2 _EPos = obj->Get2DPosition();
		Vector2 _ESize = obj->GetSize();
		if ((Get2DPosition().x > _EPos.x - _ESize.x / 2) && (Get2DPosition().x < _EPos.x + _ESize.x / 2)
			&& (Get2DPosition().y >= _EPos.y - _ESize.y / 2) && (Get2DPosition().y <= _EPos.y + _ESize.y / 2))
		{

			//m_ListEnemy.erase(m_ListEnemy.begin());
			_ListIndex.push_back(_IndexInListE);

		}
		_IndexInListE++;
	}

	for (auto obj_index : _ListIndex)
	{
		_IndexInListE = 0;
		for (auto obj_E : m_ListDodge)
		{
			if (_IndexInListE == obj_index)
			{
				m_ListDodge.erase(m_ListDodge.begin() + _IndexInListE);
				m_numberDodge++;
				std::cout << "\n Take Dodge = " << m_numberDodge++;
			}
			_IndexInListE++;
		}

	}
#pragma endregion

		

		m_horizotal = _horizontal;
		//std::cout<< " ,,, horizontal = " << m_horizotal;

		
		if (Get2DPosition().x < 10 && _horizontal >0)
		{
			Set2DPosition(Get2DPosition().x + m_Speed * _horizontal * deltatime, Get2DPosition().y);
		}
		else if (Get2DPosition().x >1270 && _horizontal <0)
		{
			Set2DPosition(Get2DPosition().x + m_Speed * _horizontal * deltatime, Get2DPosition().y);
		}
		else if (Get2DPosition().x > 10 && Get2DPosition().x <1270)
		{
			//std::cout << "\n\nCHARACTER RUNING x= "<< Get2DPosition().x;
			Set2DPosition(Get2DPosition().x + m_Speed * _horizontal * deltatime, Get2DPosition().y);
		}
		if (m_onGround)
		{
			SetTexture("Run");
		}

	}



}



void Character::Hurt(int damage)
{
	if (m_onGround)
	{
		m_Hurt = true;
		SetTexture("Hurt");
	}
	m_heal -= damage;
	if (m_heal < 0)
	{
		Death();
	}

	
}
void Character::Death()
{

}
 
void Character::ATK(std::vector<std::shared_ptr<Enemy>> &m_ListEnemy, std::vector<std::shared_ptr<Sprite2D>> &m_ListVFX)
{

	
	
	if (!m_Atk && m_CanATK)
	{	
		std::vector<int> _ListIndex;
		_ListIndex.clear();
		int _IndexInListE = 0;
		m_CanATK = false;
		m_Atk = true;
		SetTexture("Atk");

		for (auto obj : m_ListEnemy)
		{
			Vector2 _EPos = obj->Get2DPosition();
			Vector2 _ESize = obj->GetSize();
			int _CollPosX = Get2DPosition().x;


			//HardMode
			// Only blade can kill enemy
	/*		if (m_horizotal > 0)
			{
				_CollPosX += 50;
			}
			else if (m_horizotal < 0)
			{
				_CollPosX -= 50;
			}*/

			//(_CollPosX > _EPos.x - _ESize.x / 2) && (_CollPosX < _EPos.x + _ESize.x / 2)

			//easy ModE
			if (abs(_CollPosX+(m_horizotal*45) - _EPos.x)< 45
				&& (Get2DPosition().y >= _EPos.y - _ESize.y / 2) && (Get2DPosition().y <= _EPos.y + _ESize.y / 2))
			{
				if (obj->GetTypeEnemy() != 4)
				{
					_ListIndex.push_back(_IndexInListE);
				}
				else if(obj->GetTypeEnemy() == 4)
				{
					obj->Dead(Get2DPosition());
				}
				//m_ListEnemy.erase(m_ListEnemy.begin());

				
			}
			_IndexInListE++;
		}
		
		for (auto obj_index : _ListIndex)
		{
			_IndexInListE = 0;
			for (auto obj_E : m_ListEnemy)
			{
				if (_IndexInListE == obj_index)
				{
						m_ListEnemy.erase(m_ListEnemy.begin() + _IndexInListE);

						//+++++++++++++++++++++++++
						auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
						auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
						auto texture = ResourceManagers::GetInstance()->GetTexture("VFX//HITDone");
						std::shared_ptr<VFX> _VFX = std::make_shared<VFX>(model, shader, texture, 8, 0.05);
						_VFX->Set2DPosition(obj_E->Get2DPosition().x, obj_E->Get2DPosition().y);
						_VFX->SetSize(192, 192);
						m_ListVFX.push_back(_VFX);
						//========================
					
					
					
					
				}
				_IndexInListE++;
			}
			
		}
	}
}
void Character::Dodge()
{

		Set2DPosition(Get2DPosition().x + m_horizotal * 50, Get2DPosition().y);
		//std::cout << "\n Position = " << Get2DPosition().x<<" , horizontal = " <<m_horizotal;

}
void Character::Update(GLfloat deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock)
{
	AnimationSprite2D::Update(deltaTime);
	Falling(deltaTime, m_ListBlock);

	//ATK
	if(m_Atk)
	{
		//std::cout << "\n DeltaTime = " << m_time;
		m_time += deltaTime;
		
		if (m_time > 0.2f)
		{
			m_Atk = false;
			m_time = 0;
		}
	}

	if (!m_CanATK)
	{
		//std::cout << "\n DeltaTime = " << m_time;
		m_timeCanATK += deltaTime;

		if (m_timeCanATK > 0.5f)
		{
			m_CanATK = true;
			m_timeCanATK = 0;
		}
	}




	if (m_Hurt)
	{
		//std::cout << "\n DeltaTime = " << m_time;
		m_timeHurt += deltaTime;
		if (m_timeHurt > 0.15f)
		{
			m_Hurt = false;
			m_timeHurt = 0;
		}
	}


	//Jump
	if (!m_isJump /*&& m_onGround*/)
	{
		m_onGround = false;
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
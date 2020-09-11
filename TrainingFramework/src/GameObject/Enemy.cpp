
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
	std::shared_ptr<Texture> _Shield, std::shared_ptr<Texture> _StayDead,
	int _nIdle, int _nRun, int _nFall, int _nDeath, int _nAtk, int _nShield, int _nStayDeath, int _TypeEnemy)
	:m_Speed(_speed), m_heal(_heal), m_numberDodge(_numDodge), m_numBlock(_numBlock), m_jumpHeight(_jumpHeight), AnimationSprite2D(model, shader, texture, _numFrame, _frameTime)
{
	m_TypeEnemy = _TypeEnemy;
	_newPos = 0;
	m_nIdle = _nIdle;
	m_nRun = _nRun;
	m_nFall = _nFall;
	m_nDeath = _nDeath;
	m_nAtk = _nAtk;
	m_nShield = _nShield;
	m_nStayDeath = _nStayDeath;
	m_time = 0;
	m_timeATK = 0;
	m_timeWaitATK = 0;
	// use menory instead processing
	m_animIdle = _Idle;
	m_animIRun = _Run;
	m_animIFall = _Fall;
	m_animIATK = _ATK;
	m_animIShield = _Shield;
	m_animIStayDeath = _StayDead;
	doOne = false;
	m_Atk = false;
	m_CanATK = true;
}
Enemy::~Enemy() {}

int Enemy::GetTypeEnemy()
{
	return m_TypeEnemy;
}

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
			m_currentFrame = 0;
			m_numFrame = m_nAtk;
			m_pTexture = m_animIATK;
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
	if (!m_Atk)
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
			&& (Get2DPosition().y >= _BlockPos.y - _BlockSize.y / 1.2) && (Get2DPosition().y <= _BlockPos.y + _BlockSize.y / 1.2)
			&& m_isJump)
		{
			Set2DPosition(Get2DPosition().x, _BlockPos.y - _BlockSize.y / 1.22);
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

		if (_horizontal == -1 /*&& _horizontal != m_horizotal*/)
		{

			FlipY(-1.0f);
		}
		else if (_horizontal == 1 /*&& _horizontal != m_horizotal*/)
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
bool Enemy::ATk(Vector2 _PosCharacter, Vector2 _SizeCharacter)
{
	if (!m_Atk)
	{
		m_CanATK = false;
		m_Atk = true;
		SetTexture("Atk");

			Vector2 _EPos = _PosCharacter;
			Vector2 _ESize = _SizeCharacter;
			if ((Get2DPosition().x > _EPos.x - _ESize.x / 2) && (Get2DPosition().x < _EPos.x + _ESize.x / 2)
				&& (Get2DPosition().y >= _EPos.y - _ESize.y / 2) && (Get2DPosition().y <= _EPos.y + _ESize.y / 2))
			{
				//HitPlayer
				//m_ListEnemy.erase(m_ListEnemy.begin());
				return true;

			}
			else
			{
				return false;
			}
			
		}

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

	if (!m_CanATK)
	{
		//std::cout << "\n DeltaTime = " << m_time;
		m_timeWaitATK += deltaTime;
		if (m_timeWaitATK > 5.0f)
		{
			m_CanATK = true;
			m_timeWaitATK = 0;
		}
	}


	if (m_Atk)
	{
		//std::cout << "\n DeltaTime = " << m_time;
		m_timeATK += deltaTime;
		if (m_timeATK > 0.3f)
		{
			m_Atk = false;
			m_timeATK = 0;
		}
	}
}
void Enemy::Draw()
{
	AnimationSprite2D::Draw();
}

#pragma region AI
void Enemy::AiNormal(GLfloat deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock)
{

	m_time += deltaTime;

	if (m_time > 1.3)
	{
#pragma region Movement

		//std::cout << "\n mTime = " << m_time;
		//DoOne
		if (m_time > 1.3 && m_time < 1.4)
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

			_newPos = RandomFloat(_BlockPos.x - _BlockSize.x / 2, _BlockPos.x + _BlockSize.x / 2);
			// if In the Block


				// take a new Pos in the Ground
			if (_newPos < 0)
			{
				_newPos = 20;
			}
			else if (_newPos > 1280)
			{
				_newPos = 1200;
			}

			//Take Face direction
			if (_newPos < Get2DPosition().x)
			{
				//FlipY(-1);
				m_horizotal = -1;
			}
			else if (_newPos > Get2DPosition().x)
			{
				//FlipY(1);
				m_horizotal = +1;
			}


		}

		//Update
		if (m_time > 2)
		{
			Moving(m_horizotal, deltaTime);
		}


		//Moving
		if (abs(Get2DPosition().x - _newPos) <= 20)
		{

			m_time = 0;
		}
#pragma endregion


	}




}
void Enemy::AiNormal_Melle(GLfloat deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock, Vector2 _PosCharacter, Vector2 _SizeCharacter, bool& _HitPlayer)
{

	m_time += deltaTime;

	if (m_time > 1.3)
	{
#pragma region Movement
		if (abs(Get2DPosition().x - _PosCharacter.x) < 400 &&
			abs(Get2DPosition().y - _PosCharacter.y) < 50 )
		{
#pragma region MoveAnd ATK Player
			if (m_CanATK)
			{
				//_________________________CanATK=>ATK_____________________________________
				//DoOne
				if (m_time > 1.3 && m_time < 1.4)
				{
					_newPos = _PosCharacter.x;
					m_Speed = 300;
					// take a new Pos in the Ground
					if (_newPos < 0)
					{
						_newPos = 20;
					}
					else if (_newPos > 1280)
					{
						_newPos = 1200;
					}

					//Take Face direction
					if (_newPos < Get2DPosition().x)
					{
						//FlipY(-1);
						m_horizotal = -1;
					}
					else if (_newPos > Get2DPosition().x)
					{
						//FlipY(1);
						m_horizotal = +1;
					}


				}
				//To near Playert
				if (abs(Get2DPosition().x - _PosCharacter.x) < 30 &&
					abs(Get2DPosition().y - _PosCharacter.y) < 50)
				{
					_HitPlayer = ATk(_PosCharacter, _SizeCharacter);
				}
				else
				{
					if (m_time > 1.5)
					{
						Moving(m_horizotal, deltaTime);
					}
				}
				//Update

				//Moving
				if (abs(Get2DPosition().x - _newPos) <= 10)
				{

					m_time = 0;
				}
			}
			else
			{
				//-------------------------CanNotATK=> Move far the Player------------------------------

				if (m_time > 1.3 && m_time < 1.4)
				{
					//----------GET Ground Stading
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
					//---------
					if (Get2DPosition().x < _PosCharacter.x)
					{
						_newPos = RandomFloat(_BlockPos.x - _BlockSize.x / 2, _PosCharacter.x);
					}
					else if(Get2DPosition().x > _PosCharacter.x)
					{
						_newPos = RandomFloat(_PosCharacter.x, _BlockPos.x - _BlockSize.x / 2);
					}
					m_Speed = 200;
					// take a new Pos in the Ground
					if (_newPos < 0)
					{
						_newPos = 20;
					}
					else if (_newPos > 1280)
					{
						_newPos = 1200;
					}

					//Take Face direction
					if (_newPos < Get2DPosition().x)
					{
						//FlipY(-1);
						m_horizotal = -1;
					}
					else if (_newPos > Get2DPosition().x)
					{
						//FlipY(1);
						m_horizotal = +1;
					}


				}

				else
				{
					if (m_time > 2)
					{
						Moving(m_horizotal, deltaTime);
					}
				}
				//Update

				//Moving
				if (abs(Get2DPosition().x - _newPos) <= 10)
				{

					m_time = 0;
				}
				//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			}
#pragma endregion

		}
		else
		{
#pragma region MoveFree
			//std::cout << "\n mTime = " << m_time;
			//DoOne

			if (m_time > 1.3 && m_time < 1.4)
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

				_newPos = RandomFloat(_BlockPos.x - _BlockSize.x / 2, _BlockPos.x + _BlockSize.x / 2);
				// if In the Block


					// take a new Pos in the Ground
				if (_newPos < 0)
				{
					_newPos = 20;
				}
				else if (_newPos > 1280)
				{
					_newPos = 1200;
				}

				//Take Face direction
				if (_newPos < Get2DPosition().x)
				{
					//FlipY(-1);
					m_horizotal = -1;
				}
				else if (_newPos > Get2DPosition().x)
				{
					//FlipY(1);
					m_horizotal = +1;
				}
				m_Speed = 100;

			}

			//Update
			if (m_time > 2)
			{
				Moving(m_horizotal, deltaTime);
			}


			//Moving
			if (abs(Get2DPosition().x - _newPos) <= 20)
			{

				m_time = 0;
			}

			//ro detect player
			if (abs(Get2DPosition().x - _PosCharacter.x) < 400 &&
				abs(Get2DPosition().y - _PosCharacter.y) < 50)
			{
				m_time = 0;
			}
#pragma endregion
		}
#pragma endregion


	}




}
void Enemy::AiNormal_Range(GLfloat deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock, Vector2 _PosCharacter, Vector2 _SizeCharacter, bool& _HitPlayer)
{

	m_time += deltaTime;

	if (m_time > 1.3)
	{
#pragma region Movement
		if (abs(Get2DPosition().x - _PosCharacter.x) < 400 &&
			abs(Get2DPosition().y - _PosCharacter.y) < 50)
		{
#pragma region MoveAnd ATK Player
			if (m_CanATK)
			{
				//_________________________CanATK=>ATK_____________________________________
				//DoOne
				if (m_time > 1.3 && m_time < 1.4)
				{
					_newPos = _PosCharacter.x;
					m_Speed = 300;
					// take a new Pos in the Ground
					if (_newPos < 0)
					{
						_newPos = 20;
					}
					else if (_newPos > 1280)
					{
						_newPos = 1200;
					}

					//Take Face direction
					if (_newPos < Get2DPosition().x)
					{
						//FlipY(-1);
						m_horizotal = -1;
					}
					else if (_newPos > Get2DPosition().x)
					{
						//FlipY(1);
						m_horizotal = +1;
					}


				}
				//To near Playert
				if (abs(Get2DPosition().x - _PosCharacter.x) < 30 &&
					abs(Get2DPosition().y - _PosCharacter.y) < 50)
				{
					_HitPlayer = ATk(_PosCharacter, _SizeCharacter);
				}
				else
				{
					if (m_time > 1.5)
					{
						Moving(m_horizotal, deltaTime);
					}
				}
				//Update

				//Moving
				if (abs(Get2DPosition().x - _newPos) <= 10)
				{

					m_time = 0;
				}
			}
			else
			{
				//-------------------------CanNotATK=> Move far the Player------------------------------

				if (m_time > 1.3 && m_time < 1.4)
				{
					//----------GET Ground Stading
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
					//---------
					if (Get2DPosition().x < _PosCharacter.x)
					{
						_newPos = RandomFloat(_BlockPos.x - _BlockSize.x / 2, _PosCharacter.x);
					}
					else if (Get2DPosition().x > _PosCharacter.x)
					{
						_newPos = RandomFloat(_PosCharacter.x, _BlockPos.x - _BlockSize.x / 2);
					}
					m_Speed = 200;
					// take a new Pos in the Ground
					if (_newPos < 0)
					{
						_newPos = 20;
					}
					else if (_newPos > 1280)
					{
						_newPos = 1200;
					}

					//Take Face direction
					if (_newPos < Get2DPosition().x)
					{
						//FlipY(-1);
						m_horizotal = -1;
					}
					else if (_newPos > Get2DPosition().x)
					{
						//FlipY(1);
						m_horizotal = +1;
					}


				}

				else
				{
					if (m_time > 2)
					{
						Moving(m_horizotal, deltaTime);
					}
				}
				//Update

				//Moving
				if (abs(Get2DPosition().x - _newPos) <= 10)
				{

					m_time = 0;
				}
				//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			}
#pragma endregion

		}
		else
		{
#pragma region MoveFree
			//std::cout << "\n mTime = " << m_time;
			//DoOne

			if (m_time > 1.3 && m_time < 1.4)
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

				_newPos = RandomFloat(_BlockPos.x - _BlockSize.x / 2, _BlockPos.x + _BlockSize.x / 2);
				// if In the Block


					// take a new Pos in the Ground
				if (_newPos < 0)
				{
					_newPos = 20;
				}
				else if (_newPos > 1280)
				{
					_newPos = 1200;
				}

				//Take Face direction
				if (_newPos < Get2DPosition().x)
				{
					//FlipY(-1);
					m_horizotal = -1;
				}
				else if (_newPos > Get2DPosition().x)
				{
					//FlipY(1);
					m_horizotal = +1;
				}
				m_Speed = 100;

			}

			//Update
			if (m_time > 2)
			{
				Moving(m_horizotal, deltaTime);
			}


			//Moving
			if (abs(Get2DPosition().x - _newPos) <= 20)
			{

				m_time = 0;
			}

			//ro detect player
			if (abs(Get2DPosition().x - _PosCharacter.x) < 400 &&
				abs(Get2DPosition().y - _PosCharacter.y) < 50)
			{
				m_time = 0;
			}
#pragma endregion
		}
#pragma endregion


	}




}
void Enemy::AiBoss(GLfloat deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock, Vector2 _PosCharacter, Vector2 _SizeCharacter, bool& _HitPlayer)
{

	m_time += deltaTime;

	if (m_time > 1.3)
	{
#pragma region Movement

		//std::cout << "\n mTime = " << m_time;
		//DoOne
		if (m_time > 1.3 && m_time < 1.4)
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

			_newPos = RandomFloat(_BlockPos.x - _BlockSize.x / 2, _BlockPos.x + _BlockSize.x / 2);
			// if In the Block


				// take a new Pos in the Ground
			if (_newPos < 0)
			{
				_newPos = 20;
			}
			else if (_newPos > 1280)
			{
				_newPos = 1200;
			}

			//Take Face direction
			if (_newPos < Get2DPosition().x)
			{
				//FlipY(-1);
				m_horizotal = -1;
			}
			else if (_newPos > Get2DPosition().x)
			{
				//FlipY(1);
				m_horizotal = +1;
			}


		}

		//Update
		if (m_time > 2)
		{
			Moving(m_horizotal, deltaTime);
			std::cout << "\n HORICONTAL = " << m_horizotal;
			std::cout << "\n new pos === " << _newPos << ", Curren Pos == " << Get2DPosition().x;
		}


		//Moving
		if (abs(Get2DPosition().x - _newPos) <= 20)
		{

			m_time = 0;
		}
#pragma endregion


	}




}


#pragma endregion



float Enemy::RandomFloat(float min, float max)
{
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

int Enemy::Randomint(int min, int max) // inclusive
{
	return rand() % (max - min) + min + 1;
}
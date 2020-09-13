#include "GSPlay.h"
#include  <cstdlib>
#include "Application.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "AnimationSprite2D.h"
#include "Character.h"
#include <time.h>
#include <Enemy.h>
#include <Bullet.h>
#include <string>
#include "InteractOBJ.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
	m_interactMode = 0;
	m_horizontal = 0;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Falling()
{

}


void GSPlay::SpawnEnemy()
{
	
	auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader1 = ResourceManagers::GetInstance()->GetShader("AnimationShader");

#pragma region EnemyMelle
	//Enemy Anim
	std::shared_ptr<Texture> _Idle1 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Idle");
	std::shared_ptr<Texture>_Run1 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Run");
	std::shared_ptr<Texture>_Fall1 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Fall");
	std::shared_ptr<Texture>_Death1 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Death");//not Use in Normal enemy
	std::shared_ptr<Texture>_Atk1 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Atk");//not Use in Normal enemy
	std::shared_ptr<Texture>_Shield1 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy/EnemyKnight//Knight_Shield");//not Use in Normal enemy
	std::shared_ptr<Texture>_StayDeath1 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_StayDeath");//not Use in Normal enemy
	std::shared_ptr<Enemy> _Enemy1 = std::make_shared<Enemy>(50.0f, 10.0f, 5, 5, 80.0f, model1, shader1, _Idle1, 8, 0.1f,
		_Idle1, _Run1, _Fall1, _Death1, _Atk1, _Shield1, _StayDeath1, 8, 8, 1, 8, 3, 3, 5, 2/*2 = Melle Enemy*/);
	///////////////////////////////KHAI BAO

	int _numberSpawn = Randomint(1, 5);

	for (int i = 0; i < _numberSpawn; i++)
	{
		_Enemy1 = std::make_shared<Enemy>(100.0f, 10.0f, 5, 5, 80.0f, model1, shader1, _Idle1, 8, 0.1f,
			_Idle1, _Run1, _Fall1, _Death1, _Atk1, _Shield1, _StayDeath1, 8, 8, 1, 8, 3, 3, 5, 2/*2 = Mellse Enemy*/);
		_Enemy1->Set2DPosition(RandomFloat(20, 1200), 300);
		_Enemy1->SetSize(50, 50);
		m_ListEnemy.push_back(_Enemy1);
	}


			


		

	
#pragma endregion
#pragma region Archer
	_numberSpawn = Randomint(0, 3);
	for (int i = 0; i < _numberSpawn; i++)
	{
		//Archer
		_Idle1 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Idle");
		_Run1 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Run");
		_Fall1 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Fall");
		_Atk1 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Atk");//not Use in Normal enemy
		_Enemy1 = std::make_shared<Enemy>(100.0f, 10.0f, 5, 5, 80.0f, model1, shader1, _Idle1, 8, 0.1f,
			_Idle1, _Run1, _Fall1, _Death1, _Atk1, _Shield1, _StayDeath1, 8, 8, 1, 8, 5, 3, 5, 3/*3 = Range Enemy*/);
		_Enemy1->Set2DPosition(RandomFloat(20, 1200), 300);
		_Enemy1->SetSize(50, 50);
		m_ListEnemy.push_back(_Enemy1);
	}
#pragma endregion

				std::cout << "\n ENEMY COUNT == " << m_ListEnemy.size();
}

void GSPlay::Init()
{
	srand(static_cast<unsigned int>(clock()));



	m_horizontal = 0;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_1");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//BackGround
	int _ran = Randomint(0, 6);
	switch (_ran)
	{
	case 0:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_1");
		break;
	case 1:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_2");
		break;
	case 2:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_3");
		break;
	case 3:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_4");
		break;
	case 4:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_5");
		break;
	case 5:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_6");
		break;
	case 6:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_7");
		break;
	default:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_1");
		break;
	}

	


	if (Application::GetInstance()->SaveFile.isM_EndGame())
	{// Endless
		m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
		m_BackGround->Set2DPosition(screenWidth / 2.0f, screenHeight / 2.0f);
		m_BackGround->SetSize(screenWidth, screenHeight);
	}
	else
	{
		if (Application::GetInstance()->SaveFile.getM_CompletedScene() < 8)
		{
			m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
			m_BackGround->Set2DPosition(screenWidth / 2.0f, screenHeight / 2.0f);
			m_BackGround->SetSize(screenWidth, screenHeight);
		}
		else
		{
			// Boss take a new backGround
			texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_1");
			m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
			m_BackGround->Set2DPosition(screenWidth / 2.0f, screenHeight / 2.0f);
			m_BackGround->SetSize(screenWidth, screenHeight);
		}
	}



	//----------------------------Block Ground----------------------------//

	_ran = Randomint(0, 5);
	switch (_ran)
	{
	case 0:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//Ground_1");
		break;
	case 1:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//Ground_2");
		break;
	case 2:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//Ground_3");
		break;
	case 3:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//Ground_4");
		break;
	case 4:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//Ground_5");
		break;
	case 5:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//Ground_6");
		break;
	default:
		texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//Ground_1");
		break;
	}




#pragma region Gground


	if (Application::GetInstance()->SaveFile.isM_EndGame())
	{// Endless
#pragma region EndlessSpawn

		shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		
		std::shared_ptr<Sprite2D> Blocker = std::make_shared<Sprite2D>(model, shader, texture);
		Blocker->Set2DPosition(screenWidth / 2.0f, 744.0f);
		Blocker->SetSize(1280, 62);
		m_ListBlock.push_back(Blocker);

		float _PossX = RandomFloat(0, 500);
		
		if (Randomint(0, 2) == 1)
		{
			_PossX = RandomFloat(-500, 500);
		}
		else
		{
			_PossX = RandomFloat(740, 1580);
		}
		Blocker = std::make_shared<Sprite2D>(model, shader, texture);
		Blocker->Set2DPosition(_PossX, 570);
		Blocker->SetSize(1280, 62);
		m_ListBlock.push_back(Blocker);

		if (Randomint(0, 2) == 1)
		{
			_PossX = RandomFloat(-500, 500);
		}
		else
		{
			_PossX = RandomFloat(740, 1580);
		}
		Blocker = std::make_shared<Sprite2D>(model, shader, texture);
		Blocker->Set2DPosition(_PossX, 360);
		Blocker->SetSize(1280, 62);
		m_ListBlock.push_back(Blocker);

		if (Randomint(0, 2) == 1)
		{
			_PossX = RandomFloat(-500, 500);
		}
		else
		{
			_PossX = RandomFloat(740, 1580);
		}
		Blocker = std::make_shared<Sprite2D>(model, shader, texture);
		Blocker->Set2DPosition(_PossX, 150);
		Blocker->SetSize(1280, 62);
		m_ListBlock.push_back(Blocker);
#pragma endregion
	}
	else
	{
		if (Application::GetInstance()->SaveFile.getM_CompletedScene() < 8)
		{
#pragma region Spawn
			shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			
			std::shared_ptr<Sprite2D> Blocker = std::make_shared<Sprite2D>(model, shader, texture);
			Blocker->Set2DPosition(screenWidth / 2.0f, 744.0f);
			Blocker->SetSize(1280, 62);
			m_ListBlock.push_back(Blocker);

			float _PossX = RandomFloat(0, 500);
			
			if (Randomint(0, 2) == 1)
			{
				_PossX = RandomFloat(-500.0f, 500.0f);
			}
			else
			{
				_PossX = RandomFloat(740, 1580);
			}
			Blocker = std::make_shared<Sprite2D>(model, shader, texture);
			Blocker->Set2DPosition(_PossX, 570);
			Blocker->SetSize(1280, 62);
			m_ListBlock.push_back(Blocker);

			if (Randomint(0, 2) == 1)
			{
				_PossX = RandomFloat(-500, 500);
			}
			else
			{
				_PossX = RandomFloat(740, 1580);
			}
			Blocker = std::make_shared<Sprite2D>(model, shader, texture);
			Blocker->Set2DPosition(_PossX, 360);
			Blocker->SetSize(1280, 62);
			m_ListBlock.push_back(Blocker);

			if (Randomint(0, 2) == 1)
			{
				_PossX = RandomFloat(-500, 500);
			}
			else
			{
				_PossX = RandomFloat(740, 1580);
			}
			Blocker = std::make_shared<Sprite2D>(model, shader, texture);
			Blocker->Set2DPosition(_PossX, 150);
			Blocker->SetSize(1280, 62);
			m_ListBlock.push_back(Blocker);
#pragma endregion
		}
		else
		{
			//Boss only one Ground
			shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//Ground_1");
			std::shared_ptr<Sprite2D> Blocker = std::make_shared<Sprite2D>(model, shader, texture);
			Blocker->Set2DPosition(screenWidth / 2.0f, 744.0f);
			Blocker->SetSize(1280, 62);
			m_ListBlock.push_back(Blocker);

		}
	}
	
#pragma endregion



	//------------------------------------Item------------------------------------//
#pragma region Coin
	//Interaction
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("UICredits//InteractPoint");
	m_Interaction = std::make_shared<InteractOBJ>(model, shader, texture, 6, 0.1, 1);
	m_Interaction->Set2DPosition(Randomint(20, 1200), 681.0f);
	m_Interaction->SetSize(64, 64);


	//Coin
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Item//Bananas_Coin");
	std::shared_ptr<AnimationSprite2D> Item = std::make_shared<AnimationSprite2D>(model, shader, texture, 17, 0.03);
	for (auto obj : m_ListBlock)
	{
		//(x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2)
		//Caculation Blocker Location to Spawn Item on it
		Vector2 _Pos = obj->Get2DPosition();
		Vector2 _Size = obj->GetSize();
		float _PosXSpawn = RandomFloat(_Pos.x - _Size.x / 2, _Pos.x + _Size.x / 2);

		//std::cout << "\n _PosX = " << _PosXSpawn;
		int _LoopSize = Randomint(2, 6);

		// Do Not Spawn Out of the screen
		if (_PosXSpawn < 0)
		{
			_PosXSpawn = 40;
		}
		else if (_PosXSpawn > 1280)
		{
			_PosXSpawn = 800;
		}


		for (int i = 0; i < _LoopSize; i++)
		{
			// Do not Spawn Out of Ground
			if (_PosXSpawn > (_Pos.x - _Size.x / 2) && _PosXSpawn < (_Pos.x + _Size.x / 2))
			{
				Item = std::make_shared<AnimationSprite2D>(model, shader, texture, 17, 0.03);
				Item->Set2DPosition(_PosXSpawn, _Pos.y - _Size.y / 2 - 20);
				Item->SetSize(32, 32);
				m_ListCoin.push_back(Item);
				_PosXSpawn += 40;
			}


		}

	}

#pragma endregion
#pragma region Blocked Bullet
	//Blocked Bullet
	texture = ResourceManagers::GetInstance()->GetTexture("Item//Melon_BlockBullet");
	//Item = std::make_shared<AnimationSprite2D>(model, shader, texture, 17, 0.03);
	for (auto obj : m_ListBlock)
	{
		//(x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2)
		//Caculation Blocker Location to Spawn Item on it
		Vector2 _Pos = obj->Get2DPosition();
		Vector2 _Size = obj->GetSize();
		float _PosXSpawn = RandomFloat(_Pos.x - _Size.x / 2, _Pos.x + _Size.x / 2);

		//std::cout << "\n _PosX = " << _PosXSpawn;
		int _LoopSize = Randomint(1, 4);
		std::cout << "\n _LoopSize = " << _LoopSize;
		// Do Not Spawn Out of the screen
		if (_PosXSpawn < 0)
		{
			_PosXSpawn = 40;
		}
		else if (_PosXSpawn > 1280)
		{
			_PosXSpawn = 800;
		}

		std::cout << "\n _PosXSpawn = " << _PosXSpawn;
		for (int i = 0; i < _LoopSize; i++)
		{
			// Do not Spawn Out of Ground
			if (_PosXSpawn > (_Pos.x - _Size.x / 2) && _PosXSpawn < (_Pos.x + _Size.x / 2))
			{
				Item = std::make_shared<AnimationSprite2D>(model, shader, texture, 17, 0.05);
				Item->Set2DPosition(_PosXSpawn, _Pos.y - _Size.y / 2 - 40);
				Item->SetSize(32, 32);
				m_ListBlockedBullet.push_back(Item);
				_PosXSpawn += 40;
				std::cout << "\n Spawn Itemt" << Item->Get2DPosition().x;
			}


		}

	}
#pragma endregion
#pragma region //Flash
	//Flash
	texture = ResourceManagers::GetInstance()->GetTexture("Item//Cherries_Flash");
	//Item = std::make_shared<AnimationSprite2D>(model, shader, texture, 17, 0.03);
	for (auto obj : m_ListBlock)
	{
		//(x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2)
		//Caculation Blocker Location to Spawn Item on it
		Vector2 _Pos = obj->Get2DPosition();
		Vector2 _Size = obj->GetSize();
		float _PosXSpawn = RandomFloat(_Pos.x - _Size.x / 2, _Pos.x + _Size.x / 2);

		//std::cout << "\n _PosX = " << _PosXSpawn;
		int _LoopSize = Randomint(1, 4);
		std::cout << "\n _LoopSize = " << _LoopSize;
		// Do Not Spawn Out of the screen
		if (_PosXSpawn < 0)
		{
			_PosXSpawn = 40;
		}
		else if (_PosXSpawn > 1280)
		{
			_PosXSpawn = 800;
		}

		std::cout << "\n _PosXSpawn = " << _PosXSpawn;
		for (int i = 0; i < _LoopSize; i++)
		{
			// Do not Spawn Out of Ground
			if (_PosXSpawn > (_Pos.x - _Size.x / 2) && _PosXSpawn < (_Pos.x + _Size.x / 2))
			{
				Item = std::make_shared<AnimationSprite2D>(model, shader, texture, 17, 0.02);
				Item->Set2DPosition(_PosXSpawn, _Pos.y - _Size.y / 2 - 20);
				Item->SetSize(32, 32);
				m_ListDodge.push_back(Item);
				_PosXSpawn += 40;
				std::cout << "\n Spawn Itemt" << Item->Get2DPosition().x;
			}


		}

	}
#pragma endregion
	//------------------------------------Character------------------------------//
#pragma region Character

	//------------------------------Character Anim--------------------------------------//
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Character//Player//Idle");
	m_Character = std::make_shared<Character>(300.0f, 80.0f, model, shader, texture, 8, 0.1f);
	m_Character->Set2DPosition(1280 / 2, 50);
	m_Character->SetSize(200, 70);
	//m_playerCharacter = std::make_shared<Character>(10.0f, 10.0f, 5, 5);
#pragma endregion
	//______________________________________ENEMY_______________________________//
	if (Application::GetInstance()->SaveFile.isM_EndGame())
	{// Endless
#pragma region NormalEnemy
		//Enemy Anim
		//texture = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Idle");
		std::shared_ptr<Texture> _Idle5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Idle");
		std::shared_ptr<Texture> _Run5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");
		std::shared_ptr<Texture> _Fall5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Fall");
		std::shared_ptr<Texture> _Death5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDute_Death");//not Use in Normal enemy
		std::shared_ptr<Texture> _Atk5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");//not Use in Normal enemy
		std::shared_ptr<Texture> _Shield5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");//not Use in Normal enemy
		std::shared_ptr<Texture> _StayDeath5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");//not Use in Normal enemy
		std::shared_ptr<Enemy> _Enemy5 = std::make_shared<Enemy>(50.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle5, 12, 0.1f,
			_Idle5, _Run5, _Fall5, _Death5, _Atk5, _Shield5, _StayDeath5, 12, 12, 1, 7, 11, 1, 1, 1);
		for (auto obj : m_ListBlock)
		{
			//(x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2)
			//Caculation Blocker Location to Spawn Item on it
			Vector2 _Pos = obj->Get2DPosition();
			Vector2 _Size = obj->GetSize();
			float _PosXSpawn = RandomFloat(_Pos.x - _Size.x / 2, _Pos.x + _Size.x / 2);

			//std::cout << "\n _PosX = " << _PosXSpawn;
			int _LoopSize = Randomint(0, 1);

			// Do Not Spawn Out of the screen
			if (_PosXSpawn < 0)
			{
				_PosXSpawn = 40;
			}
			else if (_PosXSpawn > 1280)
			{
				_PosXSpawn = 800;
			}


			for (int i = 0; i < _LoopSize; i++)
			{
				// Do not Spawn Out of Ground
				if (_PosXSpawn > (_Pos.x - _Size.x / 2) && _PosXSpawn < (_Pos.x + _Size.x / 2))
				{
					//MaskDude
					_Idle5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Idle");
					_Run5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");
					_Fall5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Fall");
					int _ChooseSprite = Randomint(0, 3);
					switch (_ChooseSprite)
					{
					case 1:// NinJa Fog
						_Idle5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Idle");
						_Run5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Run");
						_Fall5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Fall");
						break;
					case 2:// PinkMan
						_Idle5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Idle");
						_Run5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Run");
						_Fall5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Fall");
						break;
					case 3:// Virtual Guy
						_Idle5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Idle");
						_Run5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Run");
						_Fall5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Fall");
						break;
					}

					_Enemy5 = std::make_shared<Enemy>(100.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle5, 12, 0.1f,
						_Idle5, _Run5, _Fall5, _Death5, _Atk5, _Shield5, _StayDeath5, 12, 12, 1, 7, 11, 1, 1, 1/*1 = Normal Enemy*/);
					_Enemy5->Set2DPosition(_PosXSpawn, _Pos.y - _Size.y / 2 - 20);
					_Enemy5->SetSize(50, 50);
					m_ListEnemy.push_back(_Enemy5);
					_PosXSpawn += Randomint(40, 150);

				}


			}

		}
#pragma endregion
#pragma region EnemyMelle
		//Enemy Anim
		_Idle5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Idle");
		_Run5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Run");
		_Fall5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Fall");
		_Death5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Death");//not Use in Normal enemy
		_Atk5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_ATK");//not Use in Normal enemy
		_Shield5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy/EnemyKnight//Knight_Shield");//not Use in Normal enemy
		_StayDeath5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_StayDeath");//not Use in Normal enemy
		_Enemy5 = std::make_shared<Enemy>(50.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle5, 8, 0.1f,
			_Idle5, _Run5, _Fall5, _Death5, _Atk5, _Shield5, _StayDeath5, 8, 8, 1, 8, 3, 3, 5, 2/*2 = Melle Enemy*/);
		for (auto obj : m_ListBlock)
		{
			//(x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2)
			//Caculation Blocker Location to Spawn Item on it
			Vector2 _Pos = obj->Get2DPosition();
			Vector2 _Size = obj->GetSize();
			float _PosXSpawn = RandomFloat(_Pos.x - _Size.x / 2, _Pos.x + _Size.x / 2);

			//std::cout << "\n _PosX = " << _PosXSpawn;
			int _LoopSize = Randomint(0, 2);

			// Do Not Spawn Out of the screen
			if (_PosXSpawn < 0)
			{
				_PosXSpawn = 40;
			}
			else if (_PosXSpawn > 1280)
			{
				_PosXSpawn = 800;
			}


			for (int i = 0; i < _LoopSize; i++)
			{
				// Do not Spawn Out of Ground
				if (_PosXSpawn > (_Pos.x - _Size.x / 2) && _PosXSpawn < (_Pos.x + _Size.x / 2))
				{
					//MaskDude
					_Idle5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Idle");
					_Run5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Run");
					_Fall5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Fall");
					_Death5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Death");//not Use in Normal enemy
					_Atk5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_ATK");//not Use in Normal enemy
					_Shield5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy/EnemyKnight//Knight_Shield");//not Use in Normal enemy
					_StayDeath5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_StayDeath");//not Use in Normal enemy
					//int _ChooseSprite = Randomint(0, 3);
					//switch (_ChooseSprite)
					//{
					//case 1:// NinJa Fog
					//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Idle");
					//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Run");
					//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Fall");
					//	break;
					//case 2:// PinkMan
					//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Idle");
					//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Run");
					//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Fall");
					//	break;
					//case 3:// Virtual Guy
					//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Idle");
					//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Run");
					//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Fall");
					//	break;
					//}

					_Enemy5 = std::make_shared<Enemy>(100.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle5, 8, 0.1f,
						_Idle5, _Run5, _Fall5, _Death5, _Atk5, _Shield5, _StayDeath5, 8, 8, 1, 8, 3, 3, 5, 2/*2 = Mellse Enemy*/);
					_Enemy5->Set2DPosition(_PosXSpawn, _Pos.y - _Size.y / 2 - 20);
					_Enemy5->SetSize(50, 50);
					m_ListEnemy.push_back(_Enemy5);
					_PosXSpawn += Randomint(40, 150);

				}


			}

		}
#pragma endregion
#pragma region Archer
		//Enemy Anim
		_Idle5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_IDLE");
		_Run5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Run");
		_Fall5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Fall");
		_Atk5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_ATK");//not Use in Normal enemy
		_Enemy5 = std::make_shared<Enemy>(50.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle5, 8, 0.1f,
			_Idle5, _Run5, _Fall5, _Death5, _Atk5, _Shield5, _StayDeath5, 8, 8, 1, 8, 3, 3, 5, 3/*3 = range Enemy*/);
		for (auto obj : m_ListBlock)
		{
			//(x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2)
			//Caculation Blocker Location to Spawn Item on it
			Vector2 _Pos = obj->Get2DPosition();
			Vector2 _Size = obj->GetSize();
			float _PosXSpawn = RandomFloat(_Pos.x - _Size.x / 2, _Pos.x + _Size.x / 2);

			//std::cout << "\n _PosX = " << _PosXSpawn;
			int _LoopSize = Randomint(0, 2);
			std::cout << "\n _LoopSize = " << _LoopSize;
			// Do Not Spawn Out of the screen
			if (_PosXSpawn < 0)
			{
				_PosXSpawn = 40;
			}
			else if (_PosXSpawn > 1280)
			{
				_PosXSpawn = 800;
			}

			std::cout << "\n _PosXSpawn = " << _PosXSpawn;
			for (int i = 0; i < _LoopSize; i++)
			{
				// Do not Spawn Out of Ground
				if (_PosXSpawn > (_Pos.x - _Size.x / 2) && _PosXSpawn < (_Pos.x + _Size.x / 2))
				{
					//MaskDude
					_Idle5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_IDLE");
					_Run5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Run");
					_Fall5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Fall");
					_Atk5 = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_ATK");//not Use in Normal enemy
					//int _ChooseSprite = Randomint(0, 3);
					//switch (_ChooseSprite)
					//{
					//case 1:// NinJa Fog
					//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Idle");
					//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Run");
					//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Fall");
					//	break;
					//case 2:// PinkMan
					//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Idle");
					//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Run");
					//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Fall");
					//	break;
					//case 3:// Virtual Guy
					//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Idle");
					//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Run");
					//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Fall");
					//	break;
					//}

					_Enemy5 = std::make_shared<Enemy>(100.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle5, 8, 0.1f,
						_Idle5, _Run5, _Fall5, _Death5, _Atk5, _Shield5, _StayDeath5, 8, 8, 1, 8, 5, 3, 5, 3/*3 = Range Enemy*/);
					_Enemy5->Set2DPosition(_PosXSpawn, _Pos.y - _Size.y / 2 - 20);
					_Enemy5->SetSize(50, 50);
					m_ListEnemy.push_back(_Enemy5);
					_PosXSpawn += Randomint(40, 150);

				}


			}

		}
#pragma endregion

#pragma region Bossrandom 
		if (Randomint(0, 5) == 3)
		{
		//Enemy Anim
		std::shared_ptr<Texture> _Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//Boss//Boss_IDLE");
		std::shared_ptr<Texture> _Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//Boss//Boss_Run");
		std::shared_ptr<Texture> _Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//Boss//Boss_Fall");
		std::shared_ptr<Texture> _Atk = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//Boss//Boss_ATK_2");//not Use in Normal enemy
		std::shared_ptr<Texture> _Shield = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");//not Use in Normal enemy
		std::shared_ptr<Texture> _StayDeath = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");//not Use in Normal enemy
		std::shared_ptr<Texture> _Death = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDute_Death");//not Use in Normal enemy
		std::shared_ptr<Enemy> _Enemy = std::make_shared<Enemy>(50.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle, 8, 0.1f,
			_Idle, _Run, _Fall, _Death, _Atk, _Shield, _StayDeath, 8, 8, 2, 7, 8, 3, 1, 4/*4 = Boss Enemy*/);
		_Enemy->Set2DPosition(screenWidth / 2.0f, screenHeight / 2.0f);
		_Enemy->SetSize(100, 100);
		std::cout << "\nList before push BOSS == " << m_ListEnemy.size();
		m_ListEnemy.push_back(_Enemy);
		std::cout << "\nList AFTER push  BOSS == " << m_ListEnemy.size();
	}
#pragma endregion
	}
	else
	{// no endless

		if (Application::GetInstance()->SaveFile.getM_CompletedScene() < 8)
		{
#pragma region NormalEnemy
			//Enemy Anim
			texture = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Idle");
			std::shared_ptr<Texture> _Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Idle");
			std::shared_ptr<Texture> _Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");
			std::shared_ptr<Texture> _Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Fall");
			std::shared_ptr<Texture> _Death = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDute_Death");//not Use in Normal enemy
			std::shared_ptr<Texture> _Atk = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");//not Use in Normal enemy
			std::shared_ptr<Texture> _Shield = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");//not Use in Normal enemy
			std::shared_ptr<Texture> _StayDeath = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");//not Use in Normal enemy
			std::shared_ptr<Enemy> _Enemy = std::make_shared<Enemy>(50.0f, 10.0f, 5, 5, 80.0f, model, shader, texture, 12, 0.1f,
				_Idle, _Run, _Fall, _Death, _Atk, _Shield, _StayDeath, 12, 12, 1, 7, 11, 1, 1, 1);
			for (auto obj : m_ListBlock)
			{
				//(x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2)
				//Caculation Blocker Location to Spawn Item on it
				Vector2 _Pos = obj->Get2DPosition();
				Vector2 _Size = obj->GetSize();
				float _PosXSpawn = RandomFloat(_Pos.x - _Size.x / 2, _Pos.x + _Size.x / 2);

				//std::cout << "\n _PosX = " << _PosXSpawn;
				int _LoopSize = Randomint(0, 1);

				// Do Not Spawn Out of the screen
				if (_PosXSpawn < 0)
				{
					_PosXSpawn = 40;
				}
				else if (_PosXSpawn > 1280)
				{
					_PosXSpawn = 800;
				}


				for (int i = 0; i < 1; i++)
				{
					// Do not Spawn Out of Ground
					if (_PosXSpawn > (_Pos.x - _Size.x / 2) && _PosXSpawn < (_Pos.x + _Size.x / 2))
					{
						//MaskDude
						_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Idle");
						_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");
						_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Fall");
						int _ChooseSprite = Randomint(1, 3);
						switch (_ChooseSprite)
						{
						case 1:// NinJa Fog
							_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Idle");
							_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Run");
							_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Fall");
							break;
						case 2:// PinkMan
							_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Idle");
							_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Run");
							_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Fall");
							break;
						case 3:// Virtual Guy
							_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Idle");
							_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Run");
							_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Fall");
							break;
						}

						_Enemy = std::make_shared<Enemy>(100.0f, 10.0f, 5, 5, 80.0f, model, shader, texture, 12, 0.1f,
							_Idle, _Run, _Fall, _Death, _Atk, _Shield, _StayDeath, 12, 12, 1, 7, 11, 1, 1, 1/*1 = Normal Enemy*/);
						_Enemy->Set2DPosition(_PosXSpawn, _Pos.y - _Size.y / 2 - 20);
						_Enemy->SetSize(50, 50);
						m_ListEnemy.push_back(_Enemy);
						_PosXSpawn += Randomint(40, 150);

					}


				}

			}
#pragma endregion
#pragma region EnemyMelle
			//Enemy Anim
			_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Idle");
			_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Run");
			_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Fall");
			_Death = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Death");//not Use in Normal enemy
			_Atk = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_ATK");//not Use in Normal enemy
			_Shield = ResourceManagers::GetInstance()->GetTexture("Character//Enemy/EnemyKnight//Knight_Shield");//not Use in Normal enemy
			_StayDeath = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_StayDeath");//not Use in Normal enemy
			_Enemy = std::make_shared<Enemy>(50.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle, 8, 0.1f,
				_Idle, _Run, _Fall, _Death, _Atk, _Shield, _StayDeath, 8, 8, 1, 8, 3, 3, 5, 2/*2 = Melle Enemy*/);
			for (auto obj : m_ListBlock)
			{
				//(x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2)
				//Caculation Blocker Location to Spawn Item on it
				Vector2 _Pos = obj->Get2DPosition();
				Vector2 _Size = obj->GetSize();
				float _PosXSpawn = RandomFloat(_Pos.x - _Size.x / 2, _Pos.x + _Size.x / 2);

				//std::cout << "\n _PosX = " << _PosXSpawn;
				int _LoopSize = Randomint(0, 2);

				// Do Not Spawn Out of the screen
				if (_PosXSpawn < 0)
				{
					_PosXSpawn = 40;
				}
				else if (_PosXSpawn > 1280)
				{
					_PosXSpawn = 800;
				}


				for (int i = 0; i < _LoopSize; i++)
				{
					// Do not Spawn Out of Ground
					if (_PosXSpawn > (_Pos.x - _Size.x / 2) && _PosXSpawn < (_Pos.x + _Size.x / 2))
					{
						//MaskDude
						_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Idle");
						_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Run");
						_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Fall");
						_Death = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_Death");//not Use in Normal enemy
						_Atk = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_ATK");//not Use in Normal enemy
						_Shield = ResourceManagers::GetInstance()->GetTexture("Character//Enemy/EnemyKnight//Knight_Shield");//not Use in Normal enemy
						_StayDeath = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyKnight//Knight_StayDeath");//not Use in Normal enemy
						//int _ChooseSprite = Randomint(0, 3);
						//switch (_ChooseSprite)
						//{
						//case 1:// NinJa Fog
						//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Idle");
						//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Run");
						//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Fall");
						//	break;
						//case 2:// PinkMan
						//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Idle");
						//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Run");
						//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Fall");
						//	break;
						//case 3:// Virtual Guy
						//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Idle");
						//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Run");
						//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Fall");
						//	break;
						//}

						_Enemy = std::make_shared<Enemy>(100.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle, 8, 0.1f,
							_Idle, _Run, _Fall, _Death, _Atk, _Shield, _StayDeath, 8, 8, 1, 8, 3, 3, 5, 2/*2 = Mellse Enemy*/);
						_Enemy->Set2DPosition(_PosXSpawn, _Pos.y - _Size.y / 2 - 20);
						_Enemy->SetSize(50, 50);
						m_ListEnemy.push_back(_Enemy);
						_PosXSpawn += Randomint(40, 150);

					}


				}

			}
#pragma endregion
#pragma region Archer
			//Enemy Anim
			_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_IDLE");
			_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Run");
			_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Fall");
			_Atk = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_ATK");//not Use in Normal enemy
			_Enemy = std::make_shared<Enemy>(50.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle, 8, 0.1f,
				_Idle, _Run, _Fall, _Death, _Atk, _Shield, _StayDeath, 8, 8, 1, 8, 3, 3, 5, 3/*3 = range Enemy*/);
			for (auto obj : m_ListBlock)
			{
				//(x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2)
				//Caculation Blocker Location to Spawn Item on it
				Vector2 _Pos = obj->Get2DPosition();
				Vector2 _Size = obj->GetSize();
				float _PosXSpawn = RandomFloat(_Pos.x - _Size.x / 2, _Pos.x + _Size.x / 2);

				//std::cout << "\n _PosX = " << _PosXSpawn;
				int _LoopSize = Randomint(0, 2);
				std::cout << "\n _LoopSize = " << _LoopSize;
				// Do Not Spawn Out of the screen
				if (_PosXSpawn < 0)
				{
					_PosXSpawn = 40;
				}
				else if (_PosXSpawn > 1280)
				{
					_PosXSpawn = 800;
				}

				std::cout << "\n _PosXSpawn = " << _PosXSpawn;
				for (int i = 0; i < _LoopSize; i++)
				{
					// Do not Spawn Out of Ground
					if (_PosXSpawn > (_Pos.x - _Size.x / 2) && _PosXSpawn < (_Pos.x + _Size.x / 2))
					{
						//MaskDude
						_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_IDLE");
						_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Run");
						_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_Fall");
						_Atk = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Archer_ATK");//not Use in Normal enemy
						//int _ChooseSprite = Randomint(0, 3);
						//switch (_ChooseSprite)
						//{
						//case 1:// NinJa Fog
						//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Idle");
						//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Run");
						//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//Ninja_Fall");
						//	break;
						//case 2:// PinkMan
						//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Idle");
						//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Run");
						//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//PinkMan_Fall");
						//	break;
						//case 3:// Virtual Guy
						//	_Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Idle");
						//	_Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Run");
						//	_Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//VirtualGuy_Fall");
						//	break;
						//}

						_Enemy = std::make_shared<Enemy>(100.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle, 8, 0.1f,
							_Idle, _Run, _Fall, _Death, _Atk, _Shield, _StayDeath, 8, 8, 1, 8, 5, 3, 5, 3/*3 = Range Enemy*/);
						_Enemy->Set2DPosition(_PosXSpawn, _Pos.y - _Size.y / 2 - 20);
						_Enemy->SetSize(50, 50);
						m_ListEnemy.push_back(_Enemy);
						_PosXSpawn += Randomint(40, 150);

					}


				}

			}
#pragma endregion
		}
		else
		{
#pragma region Boss
			//Enemy Anim
			std::shared_ptr<Texture> _Idle = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//Boss//Boss_IDLE");
			std::shared_ptr<Texture> _Run = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//Boss//Boss_Run");
			std::shared_ptr<Texture> _Fall = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//Boss//Boss_Fall");
			std::shared_ptr<Texture> _Atk = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//Boss//Boss_ATK_2");//not Use in Normal enemy
			std::shared_ptr<Texture> _Shield = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");//not Use in Normal enemy
			std::shared_ptr<Texture> _StayDeath = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDude_Run");//not Use in Normal enemy
			std::shared_ptr<Texture> _Death = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//BoomEnemy//MaskDute_Death");//not Use in Normal enemy
			std::shared_ptr<Enemy> _Enemy = std::make_shared<Enemy>(50.0f, 10.0f, 5, 5, 80.0f, model, shader, _Idle, 8, 0.1f,
				_Idle, _Run, _Fall, _Death, _Atk, _Shield, _StayDeath, 8, 8, 2, 7, 8, 3, 1, 4/*4 = Boss Enemy*/);
			_Enemy->Set2DPosition(screenWidth / 2.0f, screenHeight / 2.0f);
			_Enemy->SetSize(100, 100);
			std::cout << "\nList before push BOSS == " << m_ListEnemy.size();
			m_ListEnemy.push_back(_Enemy);
			std::cout << "\nList AFTER push  BOSS == " << m_ListEnemy.size();
#pragma endregion
		}

	}

	
#pragma region Text
	//text game Coin
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Coin = std::make_shared< Text>(shader, font, "10", TEXT_COLOR::BLACK, 1.0);
	m_Coin->Set2DPosition(Vector2(15, 30));
	//text game BlockBullet
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_BlockBullet = std::make_shared< Text>(shader, font, "10", TEXT_COLOR::BLACK, 1.0);
	m_BlockBullet->Set2DPosition(Vector2(50, 30));
	//text game Dodge
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Dodge = std::make_shared< Text>(shader, font, "10", TEXT_COLOR::BLACK, 1.0);
	m_Dodge->Set2DPosition(Vector2(85, 30));
#pragma endregion



}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
#pragma region Control Character
	if (bIsPressed)
	{

		switch (key)
		{
		case 'A':
			m_horizontal = -1;
			break;
		case 'D':
			m_horizontal = 1;
			break;
		case 'K':
			m_Character->Jump();
			break;
		case 'L':
			m_Character->Dodge();
			break;
		case 'J':
			m_Character->ATK(m_ListEnemy, m_ListVFX);
			Application::GetInstance()->gWave.load("..\\Data\\SFX\\atkk.wav");
			Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWave);
			break;
		case 'E':
			Vector2 _PosCharacterr = m_Character->Get2DPosition();
			if (abs(m_Interaction->Get2DPosition().x-_PosCharacterr.x) <= 50 &&
				abs(m_Interaction->Get2DPosition().y - _PosCharacterr.y)< 100)
			{
				Application::GetInstance()->gWave.load("..\\Data\\SFX\\ThrowGate.wav");
				Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWave);
				m_Interaction->DoneMapGSPlay();
			}
			break;
		}

	}

	if (!bIsPressed)
	{
		switch (key)
		{
		case 'A':
			m_horizontal = 0;
			break;

		case 'D':
			m_horizontal = 0;
			break;

		default:
			break;
		}
	}
#pragma endregion

	
	

#pragma region EditorChangeUI

	 //Use to define position in Screen (editor-> optimization is not necessary)
	//int m_Index = 1;
	//if (bIsPressed)
	//{
	//	int m_temp = 0;
	//	switch (key)
	//	{
	//	case 'A':

	//		for (auto it : m_ListBlock)
	//		{

	//			if (m_temp == m_Index)
	//			{
	//				m_temp = 0;
	//				Vector2 m_vec = it->Get2DPosition();
	//				float x = m_vec.x;
	//				float y = m_vec.y;
	//				it->Set2DPosition(x - 1, y);
	//				break;
	//			}
	//			m_temp++;
	//		}
	//		break;
	//	case 'D':
	//		for (auto it : m_ListBlock)
	//		{
	//			if (m_temp == m_Index)
	//			{
	//				m_temp = 0;
	//				Vector2 m_vec = it->Get2DPosition();
	//				float x = m_vec.x;
	//				float y = m_vec.y;
	//				it->Set2DPosition(x + 1, y);
	//				break;
	//			}
	//			m_temp++;
	//		}
	//		break;
	//	case 'W':
	//		for (auto it : m_ListBlock)
	//		{
	//			if (m_temp == m_Index)
	//			{
	//				m_temp = 0;
	//				Vector2 m_vec = it->Get2DPosition();
	//				float x = m_vec.x;
	//				float y = m_vec.y;
	//				it->Set2DPosition(x, y - 1);
	//				break;
	//			}
	//			m_temp++;
	//		}
	//		break;
	//	case 'S':
	//		for (auto it : m_ListBlock)
	//		{
	//			if (m_temp == m_Index)
	//			{
	//				m_temp = 0;
	//				Vector2 m_vec = it->Get2DPosition();
	//				float x = m_vec.x;
	//				float y = m_vec.y;
	//				it->Set2DPosition(x, y + 1);
	//				break;
	//			}
	//			m_temp++;
	//		}
	//		break;
	//	default:
	//		break;
	//	}
	//	m_temp = 0;
	//	//IN ra vi tri
	//	for (auto it : m_ListBlock)
	//	{
	//		if (m_temp == m_Index)
	//		{
	//			m_temp = 0;
	//			Vector2 m_vec = it->Get2DPosition();
	//			float x = m_vec.x;
	//			float y = m_vec.y;
	//			std::cout << "\n x = " << x << " , y = " << y <<"   , editor";
	//		}
	//		m_temp++;

	//	}
	//}
#pragma endregion
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	
	if (deltaTime != 0)
	{
		
		
		m_Character->Update(deltaTime, m_ListBlock);
		m_Character->Moving(m_horizontal, deltaTime, m_ListCoin, m_ListBlockedBullet, m_ListDodge);
		//m_playerCharacter->
		m_Interaction->Update(deltaTime, m_Character, m_interactMode);
		

		for (auto obj : m_ListCoin)
		{
			obj->Update(deltaTime);
		}
		for (auto obj : m_ListDodge)
		{
			obj->Update(deltaTime);
		}
		for (auto obj : m_ListEnemy)
		{

			obj->Update(deltaTime, m_ListBlock);
			Vector2 _PosChacter = m_Character->Get2DPosition();
			Vector2 _SizeCharacter = m_Character->GetSize();
			bool _HitPlayer = false;
			bool _SpawnEnemy = false;
			int _Type = obj->GetTypeEnemy();
			switch (_Type)
			{
			case 1://Normal
				obj->AiNormal(deltaTime, m_ListBlock);
				break;
			case 2://Melle
				obj->AiNormal_Melle(deltaTime, m_ListBlock, _PosChacter, _SizeCharacter, _HitPlayer);
				if (_HitPlayer)
				{
					m_Character->Hurt(5000);
					//+++++++++++++++++++++++++
					Application::GetInstance()->gWaveEnemy.load("..\\Data\\SFX\\ATK.wav");
					Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWaveEnemy);
					auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
					auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
					auto texture = ResourceManagers::GetInstance()->GetTexture("VFX//HITDone");
					std::shared_ptr<VFX> _VFX = std::make_shared<VFX>(model, shader, texture, 8, 0.05);
					_VFX->Set2DPosition(m_Character->Get2DPosition().x, m_Character->Get2DPosition().y);
					_VFX->SetSize(192, 192);
					m_ListVFX.push_back(_VFX);
					//========================
				}
				break;
			case 3://Range
				obj->AiNormal_Range(deltaTime, m_ListBlock, _PosChacter, _SizeCharacter, _HitPlayer);
				if (_HitPlayer)//Shoot
				{
					std::cout << "\n\n rANGEW ATK";
					Application::GetInstance()->gWaveEnemy.load("..\\Data\\SFX\\RangeATK.wav");
					Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWaveEnemy);
					auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
					auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
					auto texture = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//EnemyArcher//Arrow");
					std::shared_ptr<Bullet> _Bullet = std::make_shared<Bullet>(model, shader, texture,500, obj->GetHorizontal());
					_Bullet->Set2DPosition(obj->Get2DPosition().x, obj->Get2DPosition().y);
					_Bullet->SetSize(28, 13);
					m_ListBullet.push_back(_Bullet);
				}
				break;
			case 4://Boss
				obj->AiBoss(deltaTime, m_ListBlock, _PosChacter, _SizeCharacter, _HitPlayer, _SpawnEnemy);
				if (_HitPlayer)//Shoot
				{
					Application::GetInstance()->gWaveEnemy.load("..\\Data\\SFX\\Wind_Cast.wav");
					Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWaveEnemy);
					auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
					auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
					auto texture = ResourceManagers::GetInstance()->GetTexture("Character//Enemy//Boss//Boss_bullet_1");
					std::shared_ptr<Bullet> _Bullet = std::make_shared<Bullet>(model, shader, texture, 500, obj->GetHorizontal());
					_Bullet->Set2DPosition(obj->Get2DPosition().x, obj->Get2DPosition().y+5);
					_Bullet->SetSize(32, 32);
					_Bullet->m_IsBossOwner = true;
					m_ListBullet.push_back(_Bullet);
				}

				if (_SpawnEnemy && m_ListEnemy.size()<=1)
				{

					Application::GetInstance()->gWave.load("..\\Data\\SFX\\Spawn.wav");
					Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWave);
					std::cout << "\nList before Spawn Enemy == " << m_ListEnemy.size();
					SpawnEnemy();
					std::cout << "\nList After Spawn Enemy == " << m_ListEnemy.size();
				}
				break;
			}
		}

		if (m_ListBullet.size() != 0)
		{
			std::vector<int> _ListIndex;
			_ListIndex.clear();
			int _Index = 0;
			for (auto obj : m_ListBullet)
			{
				//upfate
				obj->Update(deltaTime, m_Character, m_ListEnemy,m_ListVFX);
				if (obj->getDES() == true)
				{
					
					_ListIndex.push_back(_Index);
				}
				_Index++;
			}

			//Delete Arrow Out of the Map
			for (auto obj_index : _ListIndex)
			{
				_Index = 0;
				for (auto obj_E : m_ListBullet)
				{
					if (_Index == obj_index)
					{
						m_ListBullet.erase(m_ListBullet.begin() + _Index);
						

					}
					_Index++;
				}

			}
			
		}

		for (auto obj : m_ListBlockedBullet)
		{
			obj->Update(deltaTime);
		}
		for (auto obj : m_ListVFX)
		{
			obj->Update(deltaTime);
		}

		int _coin = Application::GetInstance()->SaveFile.getM_Coin();
		int _BlockBullet = Application::GetInstance()->SaveFile.getM_BlockBullet();
		int _Dodge = Application::GetInstance()->SaveFile.getM_Dodge();
		m_Coin->m_text =std:: to_string(_coin);
		m_BlockBullet ->m_text = std::to_string(_BlockBullet);
		m_Dodge->m_text = std::to_string(_Dodge);
	}
}

void GSPlay::Draw()
{

	m_BackGround->Draw();

	

	for (auto obj : m_ListVFX)
	{
		obj->Draw();
	}
	m_Interaction->Draw();

	for (auto obj : m_ListBlock)
	{
		obj->Draw();
	}
	for (auto obj : m_ListCoin)
	{
		obj->Draw();
	}
	for (auto obj : m_ListBlockedBullet)
	{
		obj->Draw();
	}
	for (auto obj : m_ListDodge)
	{
		obj->Draw();
	}
	for (auto obj : m_ListEnemy)
	{
		obj->Draw();
	}
	if (m_ListBullet.size() != 0)
	{
		for (auto obj : m_ListBullet)
		{
			obj->Draw();
		}
	}


	m_Character->Draw();
	m_Coin->Draw();
	m_BlockBullet->Draw();
	m_Dodge->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}

float GSPlay::RandomFloat(float min, float max)
{
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

int GSPlay::Randomint(int min, int max) // not inclusive first
{
	return rand() % (max - min) + min + 1;
}
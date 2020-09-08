#include "GSPlay.h"
#include  <cstdlib>

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

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Falling()
{

}

void GSPlay::Init()
{
	srand(static_cast<unsigned int>(clock()));


	m_horizontal = 0;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_1");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);




	//----------------------------Block Ground----------------------------//
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//Ground_1");
	std::shared_ptr<Sprite2D> Blocker = std::make_shared<Sprite2D>(model, shader, texture);
	Blocker->Set2DPosition(screenWidth / 2, 744);
	Blocker->SetSize(1280, 62);
	m_ListBlock.push_back(Blocker);

	Blocker = std::make_shared<Sprite2D>(model, shader, texture);
	Blocker->Set2DPosition(100, screenHeight / 2 -200);
	Blocker->SetSize(1280, 62);
	m_ListBlock.push_back(Blocker);


	Blocker = std::make_shared<Sprite2D>(model, shader, texture);
	Blocker->Set2DPosition(0, screenHeight / 2+100);
	Blocker->SetSize(1280, 62);
	m_ListBlock.push_back(Blocker);





	//------------------------------------Item------------------------------------//
#pragma region Coin
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
		int _LoopSize = Randomint(4, 8);
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
				Item = std::make_shared<AnimationSprite2D>(model, shader, texture, 17, 0.03);
				Item->Set2DPosition(_PosXSpawn, _Pos.y - _Size.y / 2 - 20);
				Item->SetSize(32, 32);
				m_ListCoin.push_back(Item);
				_PosXSpawn += 40;
				std::cout << "\n Spawn Itemt" << Item->Get2DPosition().x;
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
				Item->Set2DPosition(_PosXSpawn, _Pos.y - _Size.y / 2 - 65);
				Item->SetSize(32, 32);
				m_ListFlash.push_back(Item);
				_PosXSpawn += 40;
				std::cout << "\n Spawn Itemt" << Item->Get2DPosition().x;
			}


		}

	}
#pragma endregion


	//------------------------------Character Anim--------------------------------------//
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Character//Player//Idle");
	m_Character = std::make_shared<Character>(300.0f, 10.0f, 5, 5, 80.0f , model, shader, texture, 8, 0.1f);
	m_Character->Set2DPosition(1280/2-200, 100);
	m_Character->SetSize(200, 200);
	//m_playerCharacter = std::make_shared<Character>(10.0f, 10.0f, 5, 5);
	




	////Enemy Anim
	////shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	//texture = ResourceManagers::GetInstance()->GetTexture("Character//Player//Idle");
	//std::shared_ptr<AnimationSprite2D> Enemy = std::make_shared<AnimationSprite2D>(model, shader, texture,8,0.1f);
	//Enemy->Set2DPosition(screenWidth / 2, screenHeight / 4);
	//Enemy->SetSize(200, 200);
	//m_ListEnemy.push_back(Enemy);




	////text game title
	//shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	//std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	//m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	//m_score->Set2DPosition(Vector2(5, 25));

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
		case 'B':
			m_Character->Jump();
			break;
		case 'F':
			m_Character->Dodge();
			break;
		default:
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
	m_Character->Update(deltaTime, m_ListBlock);
	m_Character->Moving(m_horizontal, deltaTime);
	//m_playerCharacter->


	for (auto obj : m_ListEnemy)
	{
		obj->Update(deltaTime);
		//obj->Draw();
	}

	for (auto obj : m_ListCoin)
	{
		obj->Update(deltaTime);
	}
	for (auto obj : m_ListFlash)
	{
		obj->Update(deltaTime);
	}


	for (auto obj : m_ListBlockedBullet)
	{
		obj->Update(deltaTime);
	}
}

void GSPlay::Draw()
{

	m_BackGround->Draw();
	//m_score->Draw();


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
	for (auto obj : m_ListFlash)
	{
		obj->Draw();
	}
	for (auto obj : m_ListEnemy)
	{
		obj->Draw();
	}


	m_Character->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}

float GSPlay::RandomFloat(float min, float max)
{
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

int GSPlay::Randomint(int min, int max) // inclusive
{
	return rand() % (max - min) + min + 1;
}
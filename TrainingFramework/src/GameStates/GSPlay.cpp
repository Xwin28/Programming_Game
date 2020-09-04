#include "GSPlay.h"

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
	m_horizontal = 0;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);
	



	//Character Anim
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Character//Player//Idle");
	//m_Character = std::make_shared<AnimationSprite2D>(model, shader, texture, 8, 0.1f);
	m_Character = std::make_shared<Character>(300.0f, 10.0f, 5, 5, 80.0f , model, shader, texture, 8, 0.1f);
	m_Character->Set2DPosition(1280/2, 100);
	m_Character->SetSize(200, 200);
	//m_playerCharacter = std::make_shared<Character>(10.0f, 10.0f, 5, 5);
	

	//Enemy Anim
	//shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Character//Player//Idle");
	std::shared_ptr<AnimationSprite2D> Enemy = std::make_shared<AnimationSprite2D>(model, shader, texture,8,0.1f);
	Enemy->Set2DPosition(screenWidth / 2, screenHeight / 4);
	Enemy->SetSize(200, 200);
	m_ListEnemy.push_back(Enemy);
	

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
	

#pragma region EditorChangeUI

	// Use to define position in Screen (editor-> optimization is not necessary)
	//int m_Index = 0;
	//if (bIsPressed)
	//{
	//	int m_temp = 0;
	//	switch (key)
	//	{
	//	case 'A':

	//		for (auto it : m_ListEnemy)
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
	//		for (auto it : m_ListEnemy)
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
	//		for (auto it : m_ListEnemy)
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
	//		for (auto it : m_ListEnemy)
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
	//	for (auto it : m_ListEnemy)
	//	{
	//		if (m_temp == m_Index)
	//		{
	//			m_temp = 0;
	//			Vector2 m_vec = it->Get2DPosition();
	//			float x = m_vec.x;
	//			float y = m_vec.y;
	//			std::cout << "\n x = " << x << " , y = " << y;
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
	m_Character->Update(deltaTime);
	m_Character->Moving(m_horizontal, deltaTime);
	//m_playerCharacter->
	for (auto obj : m_ListEnemy)
	{
		obj->Update(deltaTime);
		//obj->Draw();
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_Character->Draw();
	//m_score->Draw();
	for (auto obj : m_ListEnemy)
	{
		obj->Draw();
	}
}

void GSPlay::SetNewPostionForBullet()
{
}
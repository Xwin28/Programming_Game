#include "GSHome.h"
#include "GSHome.h"
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


GSHome::GSHome()
{
	
}


GSHome::~GSHome()
{
}





void GSHome::Init()
{
	srand(static_cast<unsigned int>(clock()));


	m_horizontal = 0;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//BackGround_home");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);




	//----------------------------Block Ground----------------------------//
#pragma region Gground
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Scene//Scene_1//Ground_home");
	std::shared_ptr<Sprite2D> Blocker = std::make_shared<Sprite2D>(model, shader, texture);
	Blocker->Set2DPosition(screenWidth / 2, 744);
	Blocker->SetSize(1280, 62);
	m_ListBlock.push_back(Blocker);



#pragma endregion



	//------------------------------------Item------------------------------------//
#pragma region Interaction
	//Interaction
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("UICredits//Heal_Inter");
	m_PlusHeal = std::make_shared<InteractOBJ>(model, shader, texture, 6, 0.1, 1);
	m_PlusHeal->Set2DPosition(540, 650);
	m_PlusHeal->SetSize(64, 124);
	//Interaction

	texture = ResourceManagers::GetInstance()->GetTexture("UICredits//DamageInter");
	m_PlusDamage= std::make_shared<InteractOBJ>(model, shader, texture, 6, 0.1, 2);
	m_PlusDamage->Set2DPosition(840, 650);
	m_PlusDamage->SetSize(64, 124);
	//Interaction

	texture = ResourceManagers::GetInstance()->GetTexture("UICredits//InteractPoint");
	m_Gate = std::make_shared<InteractOBJ>(model, shader, texture, 6, 0.1, 2);
	m_Gate->Set2DPosition(1200, 681);
	m_Gate->SetSize(64, 64);
	

#pragma endregion

	//------------------------------------Character------------------------------//
#pragma region Character

	//------------------------------Character Anim--------------------------------------//
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Character//Player//Idle");
	m_Character = std::make_shared<Character>(300.0f, 80.0f, model, shader, texture, 8, 0.1f);
	m_Character->Set2DPosition(300, 700);
	m_Character->SetSize(200, 70);
	//m_playerCharacter = std::make_shared<Character>(10.0f, 10.0f, 5, 5);


	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	if (Application::GetInstance()->SaveFile.isM_EndGame())
	{
		shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
		texture = ResourceManagers::GetInstance()->GetTexture("Character//Player//Nurse");
		m_Nurse = std::make_shared<AnimationSprite2D>(model, shader, texture, 4, 0.5f);
		m_Nurse->Set2DPosition(300, 690);
		m_Nurse->SetSize(60, 60);



		//text game END
		shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		font = ResourceManagers::GetInstance()->GetFont("arialbd");
		m_End = std::make_shared< Text>(shader, font, "Congratulations!! you had save your Waifu!", TEXT_COLOR::RED, 1.3);
		m_End->Set2DPosition(Vector2(screenWidth/2-350, screenHeight/2));
	}


#pragma endregion






#pragma region Text
	//text game Coin
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	m_Coin = std::make_shared< Text>(shader, font, "10", TEXT_COLOR::BLACK, 1.0);
	m_Coin->Set2DPosition(Vector2(15, 30));
	//text game BlockBullet
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	m_BlockBullet = std::make_shared< Text>(shader, font, "10", TEXT_COLOR::BLACK, 1.0);
	m_BlockBullet->Set2DPosition(Vector2(50, 30));
	//text game Dodge
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	m_Dodge = std::make_shared< Text>(shader, font, "10", TEXT_COLOR::BLACK, 1.0);
	m_Dodge->Set2DPosition(Vector2(85, 30));

	//text game Dodge
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	m_txtDame = std::make_shared< Text>(shader, font, "Damage: 10", TEXT_COLOR::BLUE, 1.0);
	m_txtDame->Set2DPosition(Vector2(100, 520));
	//text game Dodge
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	m_txtHeal = std::make_shared< Text>(shader, font, "Heal = 10", TEXT_COLOR::RED, 1.0);
	m_txtHeal->Set2DPosition(Vector2(100, 560));

#pragma endregion



}

void GSHome::Exit()
{

}


void GSHome::Pause()
{

}

void GSHome::Resume()
{

}


void GSHome::HandleEvents()
{

}

void GSHome::HandleKeyEvents(int key, bool bIsPressed)
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
			break;
		case 'E':
			Vector2 _PosCharacterr = m_Character->Get2DPosition();
			if (abs(m_PlusHeal->Get2DPosition().x - _PosCharacterr.x) <= 50 &&
				abs(m_PlusHeal->Get2DPosition().y - _PosCharacterr.y) < 100)
			{
				m_PlusHeal->PlusHeal();
				
			}
			else if (abs(m_PlusDamage->Get2DPosition().x - _PosCharacterr.x) <= 50 &&
					abs(m_PlusDamage->Get2DPosition().y - _PosCharacterr.y) < 100)
			{
				m_PlusDamage->PlusDamage();

			}
			else if (abs(m_Gate->Get2DPosition().x - _PosCharacterr.x) <= 50 &&
				abs(m_Gate->Get2DPosition().y - _PosCharacterr.y) < 100)
			{
				m_Gate->ToWar();// go to GSPlay

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

void GSHome::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSHome::Update(float deltaTime)
{

	if (deltaTime != 0)
	{


		m_Character->Update(deltaTime, m_ListBlock);
		m_Character->Moving(m_horizontal, deltaTime, m_ListCoin, m_ListBlockedBullet, m_ListDodge);
		//m_playerCharacter->
		m_PlusHeal->Update(deltaTime, m_Character, m_interactMode);
		m_PlusDamage->Update(deltaTime, m_Character, m_interactMode);
		m_Gate->Update(deltaTime, m_Character, m_interactMode);

		int _coin = Application::GetInstance()->SaveFile.getM_Coin();
		int _BlockBullet = Application::GetInstance()->SaveFile.getM_BlockBullet();
		int _Dodge = Application::GetInstance()->SaveFile.getM_Dodge();

		int _dame = Application::GetInstance()->SaveFile.m_damage;
		int _heal = Application::GetInstance()->SaveFile.m_heal;

		m_Coin->m_text = std::to_string(_coin);
		m_BlockBullet->m_text = std::to_string(_BlockBullet);
		m_Dodge->m_text = std::to_string(_Dodge);
		m_txtDame->m_text = "Damage: " + std::to_string(_dame);
		m_txtHeal->m_text = "Heal: " + std::to_string(_heal);

		if (Application::GetInstance()->SaveFile.isM_EndGame())
		{
			m_Nurse->Update(deltaTime);
		}
	}
}

void GSHome::Draw()
{

	m_BackGround->Draw();



	
	m_PlusHeal->Draw();
	m_PlusDamage->Draw();
	m_Gate->Draw();
	for (auto obj : m_ListBlock)
	{
		//obj->Draw();
	}
	

	if (Application::GetInstance()->SaveFile.isM_EndGame())
	{	
		m_End->Draw();
		m_Nurse->Draw();
	}


	m_Character->Draw();
	m_Coin->Draw();
	m_BlockBullet->Draw();
	m_Dodge->Draw();



	m_txtDame->Draw();
	m_txtHeal->Draw();
}

void GSHome::SetNewPostionForBullet()
{
}

float GSHome::RandomFloat(float min, float max)
{
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

int GSHome::Randomint(int min, int max) // inclusive
{
	return rand() % (max - min) + min + 1;
}
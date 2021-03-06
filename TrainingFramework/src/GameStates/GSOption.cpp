#include "GSOption.h"
#include <iostream>
#include "Application.h"
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSOption::GSOption()
{

}


GSOption::~GSOption()
{
}



void GSOption::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UIMenu//Night");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Name of the Game, and all UI designed
	texture = ResourceManagers::GetInstance()->GetTexture("UIOption//UIOption");
	m_Image = std::make_shared<Sprite2D>(model, shader, texture);
	m_Image->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_Image->SetSize(screenWidth, screenHeight);


	//Button OK
	texture = ResourceManagers::GetInstance()->GetTexture("UIOption//btn_OK");
	auto button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(613, 655);
	button->SetSize(136, 86);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		Application::GetInstance()->gWave.load("..\\Data\\SFX\\Click.wav");
		Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWave);
		});
	m_listButton.push_back(button);


}

void GSOption::Exit()
{
}


void GSOption::Pause()
{

}

void GSOption::Resume()
{

}


void GSOption::HandleEvents()
{

}

void GSOption::HandleKeyEvents(int key, bool bIsPressed)
{


//#pragma region EditorChangeUI
//
//	// Use to define position in Screen (editor-> optimization is not necessary)
//	int m_Index = 4;
//	if (bIsPressed)
//	{
//		int m_temp = 0;
//		switch (key)
//		{
//		case 'A':
//
//			for (auto it : m_listButton)
//			{
//
//				if (m_temp == m_Index)
//				{
//					m_temp = 0;
//					Vector2 m_vec = it->Get2DPosition();
//					float x = m_vec.x;
//					float y = m_vec.y;
//					it->Set2DPosition(x - 1, y);
//					break;
//				}
//				m_temp++;
//			}
//			break;
//		case 'D':
//			for (auto it : m_listButton)
//			{
//				if (m_temp == m_Index)
//				{
//					m_temp = 0;
//					Vector2 m_vec = it->Get2DPosition();
//					float x = m_vec.x;
//					float y = m_vec.y;
//					it->Set2DPosition(x + 1, y);
//					break;
//				}
//				m_temp++;
//			}
//			break;
//		case 'W':
//			for (auto it : m_listButton)
//			{
//				if (m_temp == m_Index)
//				{
//					m_temp = 0;
//					Vector2 m_vec = it->Get2DPosition();
//					float x = m_vec.x;
//					float y = m_vec.y;
//					it->Set2DPosition(x, y - 1);
//					break;
//				}
//				m_temp++;
//			}
//			break;
//		case 'S':
//			for (auto it : m_listButton)
//			{
//				if (m_temp == m_Index)
//				{
//					m_temp = 0;
//					Vector2 m_vec = it->Get2DPosition();
//					float x = m_vec.x;
//					float y = m_vec.y;
//					it->Set2DPosition(x, y + 1);
//					break;
//				}
//				m_temp++;
//			}
//			break;
//		default:
//			break;
//		}
//		m_temp = 0;
//		//IN ra vi tri
//		for (auto it : m_listButton)
//		{
//			if (m_temp == m_Index)
//			{
//				m_temp = 0;
//				Vector2 m_vec = it->Get2DPosition();
//				float x = m_vec.x;
//				float y = m_vec.y;
//				std::cout << "\n x = " << x << " , y = " << y;
//			}
//			m_temp++;
//
//		}
//	}
//#pragma endregion

}

void GSOption::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSOption::Update(float deltaTime)
{

	m_BackGround->Update(deltaTime);
	m_Image->Draw();
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSOption::Draw()
{
	m_BackGround->Draw();
	m_Image->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	//m_Text_gameName->Draw();
}
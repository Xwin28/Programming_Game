#include "GSCredits.h"
#include <iostream>
#include "Application.h"
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSCredits::GSCredits()
{

}


GSCredits::~GSCredits()
{
}



void GSCredits::Init()
{
	std::cout << "SHOW CREDIT";
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UIMenu//Night");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Name of the Game, and all UI designed
	texture = ResourceManagers::GetInstance()->GetTexture("UICredits//UICredit");
	m_Image = std::make_shared<Sprite2D>(model, shader, texture);
	m_Image->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_Image->SetSize(screenWidth, screenHeight);


	//OK button
	texture = ResourceManagers::GetInstance()->GetTexture("UIOption//btn_OK");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(631, 618);
	button->SetSize(136, 86);
	button->SetOnClick([]() {
		Application::GetInstance()->gWave.load("..\\Data\\SFX\\Click.wav");
		Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWave);
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);


	////OptionButton
	//texture = ResourceManagers::GetInstance()->GetTexture("UIMenu//UIbtn_Option");
	//button = std::make_shared<GameButton>(model, shader, texture);
	//button->Set2DPosition(313, 536);
	//button->SetSize(337, 86);
	//button->SetOnClick([]() {
	//	GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	//	});
	//m_listButton.push_back(button);


	////CreditButton
	//texture = ResourceManagers::GetInstance()->GetTexture("UIMenu//UIbtn_Credits");
	//button = std::make_shared<GameButton>(model, shader, texture);
	//button->Set2DPosition(313, 653);
	//button->SetSize(379, 82);
	//button->SetOnClick([]() {
	//	GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	//	});
	//m_listButton.push_back(button);


	////exit button// Use X to Exit
	//texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	//button = std::make_shared<GameButton>(model, shader, texture);
	//button->Set2DPosition(screenWidth / 2, 300);
	//button->SetSize(200, 50);
	//button->SetOnClick([]() {
	//	exit(0);
	//	});
	//m_listButton.push_back(button);


	////text game title
	//shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	//std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	//m_Text_gameName = std::make_shared< Text>(shader, font, "SAMPLE NAME", TEXT_COLOR::GREEN, 1.0);
	//m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 80, 120));
}

void GSCredits::Exit()
{
}


void GSCredits::Pause()
{

}

void GSCredits::Resume()
{

}


void GSCredits::HandleEvents()
{

}

void GSCredits::HandleKeyEvents(int key, bool bIsPressed)
{


#pragma region EditorChangeUI

	// Use to define position in Screen (editor-> optimization is not necessary)
	int m_Index = 0;
	if (bIsPressed)
	{
		int m_temp = 0;
		switch (key)
		{
		case 'A':

			for (auto it : m_listButton)
			{

				if (m_temp == m_Index)
				{
					m_temp = 0;
					Vector2 m_vec = it->Get2DPosition();
					float x = m_vec.x;
					float y = m_vec.y;
					it->Set2DPosition(x - 1, y);
					break;
				}
				m_temp++;
			}
			break;
		case 'D':
			for (auto it : m_listButton)
			{
				if (m_temp == m_Index)
				{
					m_temp = 0;
					Vector2 m_vec = it->Get2DPosition();
					float x = m_vec.x;
					float y = m_vec.y;
					it->Set2DPosition(x + 1, y);
					break;
				}
				m_temp++;
			}
			break;
		case 'W':
			for (auto it : m_listButton)
			{
				if (m_temp == m_Index)
				{
					m_temp = 0;
					Vector2 m_vec = it->Get2DPosition();
					float x = m_vec.x;
					float y = m_vec.y;
					it->Set2DPosition(x, y - 1);
					break;
				}
				m_temp++;
			}
			break;
		case 'S':
			for (auto it : m_listButton)
			{
				if (m_temp == m_Index)
				{
					m_temp = 0;
					Vector2 m_vec = it->Get2DPosition();
					float x = m_vec.x;
					float y = m_vec.y;
					it->Set2DPosition(x, y + 1);
					break;
				}
				m_temp++;
			}
			break;
		default:
			break;
		}
		m_temp = 0;
		//IN ra vi tri
		for (auto it : m_listButton)
		{
			if (m_temp == m_Index)
			{
				m_temp = 0;
				Vector2 m_vec = it->Get2DPosition();
				float x = m_vec.x;
				float y = m_vec.y;
				std::cout << "\n x = " << x << " , y = " << y;
			}
			m_temp++;

		}
	}
#pragma endregion

}

void GSCredits::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSCredits::Update(float deltaTime)
{

	m_BackGround->Update(deltaTime);
	m_Image->Draw();
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSCredits::Draw()
{
	m_BackGround->Draw();
	m_Image->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	//m_Text_gameName->Draw();
}
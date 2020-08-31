#include "GSOption.h"
#include <iostream>

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


	//Music Volume Right button
	texture = ResourceManagers::GetInstance()->GetTexture("UIOption//Volume_right");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(901, 285);
	button->SetSize(35, 67);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//Music Volume Left button
	texture = ResourceManagers::GetInstance()->GetTexture("UIOption//Volume_left");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(807, 285);
	button->SetSize(45, 67);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//SFX Volume Right button
	texture = ResourceManagers::GetInstance()->GetTexture("UIOption//Volume_right");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(901, 385);
	button->SetSize(35, 67);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//SFX Volume Left button
	texture = ResourceManagers::GetInstance()->GetTexture("UIOption//Volume_left");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(807, 385);
	button->SetSize(45, 67);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);



	//Button OK
	texture = ResourceManagers::GetInstance()->GetTexture("UIOption//btn_OK");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(613, 655);
	button->SetSize(136, 86);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
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


#pragma region EditorChangeUI

	// Use to define position in Screen (editor-> optimization is not necessary)
	int m_Index = 4;
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
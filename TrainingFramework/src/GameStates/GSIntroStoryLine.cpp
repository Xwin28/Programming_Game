#include "GSIntroStoryLine.h"
#include "Application.h"
#include <iostream>
#include <GameButton.h>
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


GSIntroStoryLine::GSIntroStoryLine()
{
	m_time = 0;
}


GSIntroStoryLine::~GSIntroStoryLine()
{
}


void GSIntroStoryLine::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UICredits//IntroStory");

	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_logo->SetSize(721, 509);



	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("UIMenu//UIbtn_Play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, screenHeight / 2+150);
	button->SetSize(264, 89);
	button->SetOnClick([]() {
		std::cout << "\n run";
		// 0= load IntroStoryline, 1 = load Home, 2 = load GSPLay, 3 = Load GSMenu
		Application::GetInstance()->SaveFile.setM_IntroScene(true);
		Application::GetInstance()->SaveFile.Save();
		Application::GetInstance()->SaveFile.m_SceneManage = 1;
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
}

void GSIntroStoryLine::Exit()
{
	
}


void GSIntroStoryLine::Pause()
{
	
}

void GSIntroStoryLine::Resume()
{
	
}


void GSIntroStoryLine::HandleEvents()
{
	
}

void GSIntroStoryLine::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSIntroStoryLine::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSIntroStoryLine::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSIntroStoryLine::Draw()
{
	m_logo->Draw();

	//for (auto obj : m_listButton)
	//{
	//	//obj->Draw();
	//}
}

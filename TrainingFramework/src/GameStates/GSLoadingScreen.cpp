#include "GSLoadingScreen.h"
#include "Application.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


GSLoadingScreen::GSLoadingScreen()
{
	m_time = 0;
}


GSLoadingScreen::~GSLoadingScreen()
{
}


void GSLoadingScreen::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UICredits//Loading");

	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_logo->SetSize(1280, 768);
}

void GSLoadingScreen::Exit()
{
	
}


void GSLoadingScreen::Pause()
{
	
}

void GSLoadingScreen::Resume()
{
	
}


void GSLoadingScreen::HandleEvents()
{
	
}

void GSLoadingScreen::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSLoadingScreen::HandleTouchEvents(int x, int y, bool bIsPressed)
{

}

void GSLoadingScreen::Update(float deltaTime)
{



	//m_time += deltaTime;
	//if (m_time > 0.5)
	//{
	//	GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	//	m_time = 0;
	//}






#pragma region Load
	int _SceneManage = Application::GetInstance()->SaveFile.m_SceneManage;
	bool _isintroStory = Application::GetInstance()->SaveFile.isM_IntroScene();
	if (_SceneManage == 0 && _isintroStory)
	{
		_SceneManage = 1;// if Introed => do not play intro any more
	}

	// 0= load IntroStoryline, 1 = load Home, 2 = load GSPLay, 3 = Load GSMenu
	switch (_SceneManage)
	{
	case 0:
		m_time += deltaTime;
		if (m_time > 0.5)
		{
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_IntroStoryLine);
			m_time = 0;
		}
		break;
		break;
	case 1:
		m_time += deltaTime;
		if (m_time > 0.5)
		{
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Home);
			m_time = 0;
		}
		break;
	case 2:
		m_time += deltaTime;
		if (m_time > 0.5)
		{
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
			m_time = 0;
		}
		break;
	case 3:
		m_time += deltaTime;
		if (m_time > 0.5)
		{
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
			m_time = 0;
		}
		break;
	}
#pragma endregion

	

}

void GSLoadingScreen::Draw()
{
	m_logo->Draw();
}

#include "Application.h"
#include "GameStates/GameStateMachine.h"
#include "GameStates/GameStatebase.h"

#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_thread.h"

extern GLint screenWidth;
extern GLint screenHeight;


Application::Application()
{
}


Application::~Application()
{
}


void Application::Init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Intro);
	//SoLoud::Soloud gSoloud; // SoLoud engine
	gSoloud.init();
	//gWave.load("..\\Data\\SFX\\jojo.wav");
	//gSoloud.play(gWave);
	//int x = gSoloud.play(gWave); // Grab the handle
	//gSoloud.setPan(x, -0.2f);    // Use handle to adjust panning
}

void Application::Update(GLfloat deltaTime)
{
	GameStateMachine::GetInstance()->PerformStateChange();

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Update(deltaTime);
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Draw();
}

void Application::HandleKeyEvent(unsigned char key, bool bIsPresseded)
{
	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleKeyEvents(key, bIsPresseded);

}

void Application::HandleTouchEvent(GLint x, GLint y, bool bIsPresseded)
{

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(x, y, bIsPresseded);
}

void Application::Exit()
{
	gSoloud.deinit();
	exit(0);
}

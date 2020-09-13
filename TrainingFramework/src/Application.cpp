#include "Application.h"
#include "GameStates/GameStateMachine.h"
#include "GameStates/GameStatebase.h"

#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_thread.h"
#include "SavingSystem/SavingSys.h"
//#include <experimental/filesystem>
#include <filesystem>
extern GLint screenWidth;
extern GLint screenHeight;

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

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
	
	gSoloud.init();
	gSoloudMusic.init();
	//gWave.load("..\\Data\\SFX\\jojo.wav");
	//gSoloud.play(gWave);
	//int x = gSoloud.play(gWave); // Grab the handle
	//gSoloud.setPan(x, -0.2f);    // Use handle to adjust panning


	Application::GetInstance()->gWaveMusic.load("..\\Data\\SFX\\jwick.wav");
	int x = Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWaveMusic);
	gSoloudMusic.setVolume(x, 0.2);
#pragma region Saving
	//std::experimental::filesystem::exists("..\\Data\\SAVE_FILE\\Save.txt")
	//std::filesystem::exists("..\\Data\\SAVE_FILE\\Save.txt")
	if (std::filesystem::exists("..\\Data\\SAVE_FILE\\Save.txt"))
	{
		std::cout << "\n HAS FILE\n";
		SaveFile.Load();
	}
	else
	{
		std::cout << "\n DO NOT HAS FILE\n";
		SaveFile:SavingSys();
		SaveFile.Save();
	}
#pragma endregion

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

#include "InteractOBJ.h"
#include "Character.h"
#include "AnimationSprite2D.h"
#include "Sprite2D.h"
#include "Application.h"
#include "GameStates/GameStateMachine.h"


InteractOBJ::InteractOBJ(){}
InteractOBJ::InteractOBJ(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime, int _mode):
			AnimationSprite2D(model, shader, texture, _numFrame, _frameTime), m_mode(_mode)
{

}

// 0= load IntroStoryline, 1 = load Home, 2 = load GSPLay, 3 = Load GSMenu


void InteractOBJ::PlusHeal()
{
	int _heal = Application::GetInstance()->SaveFile.m_heal;
	int _coin = Application::GetInstance()->SaveFile.getM_Coin();
	if (_coin >= 15)
	{
		Application::GetInstance()->gWave.load("..\\Data\\SFX\\HealthPickup.wav");
		Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWave);
		Application::GetInstance()->SaveFile.m_heal = _heal + 1;
		int _coin = Application::GetInstance()->SaveFile.getM_Coin();
		Application::GetInstance()->SaveFile.setM_Coin(_coin - 15);
		Application::GetInstance()->SaveFile.Save();
	}
	else
	{
		Application::GetInstance()->gWave.load("..\\Data\\SFX\\Error_1.wav");
		Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWave);
	}
}
void InteractOBJ::PlusDamage()
{
	Application::GetInstance()->gWave.load("..\\Data\\SFX\\HealthPickup.wav");
	Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWave);
	int _damage = Application::GetInstance()->SaveFile.m_damage;
	int _coin = Application::GetInstance()->SaveFile.getM_Coin();
	if (_coin >= 15)
	{
		Application::GetInstance()->SaveFile.m_damage = _damage + 1;
		int _coin = Application::GetInstance()->SaveFile.getM_Coin();
		Application::GetInstance()->SaveFile.setM_Coin(_coin - 15);
		Application::GetInstance()->SaveFile.Save();
	}
	else
	{
		Application::GetInstance()->gWave.load("..\\Data\\SFX\\Error_1.wav");
		Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWave);
	}
}
int InteractOBJ::getMode()
{
	return m_mode;
}

void InteractOBJ::ToWar()
{
	Application::GetInstance()->gWave.load("..\\Data\\SFX\\ThrowGate.wav");
	Application::GetInstance()->gSoloud.play(Application::GetInstance()->gWave);
	Application::GetInstance()->SaveFile.m_SceneManage = 2;
	GameStateMachine::GetInstance()->PopState();
}
void InteractOBJ::DoneMapGSPlay()
{
		int _completeScene = Application::GetInstance()->SaveFile.getM_CompletedScene();
		Application::GetInstance()->SaveFile.setM_CompletedScene(_completeScene + 1);
		Application::GetInstance()->SaveFile.m_SceneManage = 2;
		Application::GetInstance()->SaveFile.Save();
		GameStateMachine::GetInstance()->PopState();
}
void InteractOBJ::ToMenu()
{
		Application::GetInstance()->SaveFile.m_SceneManage = 3;
		GameStateMachine::GetInstance()->PopState();
}
void InteractOBJ::Init()
{
	AnimationSprite2D::Init();
}
void InteractOBJ::Draw()
{
	AnimationSprite2D::Draw();

}
void InteractOBJ::Update(GLfloat deltatime, std::shared_ptr<Character>  m_Character, int &interactedMode)
{
	AnimationSprite2D::Update(deltatime);
	interactedMode = m_mode;

}
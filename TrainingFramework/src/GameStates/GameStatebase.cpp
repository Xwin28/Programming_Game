/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSOption.h"
#include "GSCredits.h"
#include "GameStatebase.h"
#include "GSIntroStoryLine.h"
#include "GSLoadingScreen.h"
#include "GSHome.h"


std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case STATE_INVALID:
		break;
	case STATE_Intro:
		gs = std::make_shared<GSIntro>();
		break;
	case STATE_Menu:
		gs = std::make_shared<GSMenu>();
		break;
	case STATE_Play:
		gs = std::make_shared<GSPlay>();
		break;
	case STATE_Option:
		gs = std::make_shared<GSOption>();
		break;
	case STATE_Credit:
		gs = std::make_shared<GSCredits>();
		break;
	case STATE_LoadingScreen:
		gs = std::make_shared<GSLoadingScreen>();
		break;
	case STATE_IntroStoryLine:
		gs = std::make_shared<GSIntroStoryLine>();
		break;
	case STATE_Home:
		gs = std::make_shared<GSHome>();
		break;
	default:
		break;
	}
	return gs;
}
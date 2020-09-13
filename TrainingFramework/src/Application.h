#pragma once
#include "Singleton.h"
#include "GameConfig.h"

#include "SavingSystem/SavingSys.h"
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_thread.h"

class Application : public CSingleton<Application>
{
public:
	Application();
	~Application();
	void		Init();
	void		Update( GLfloat deltaTime);
	void		Render();
	void		HandleKeyEvent(unsigned char key, bool bIsPresseded);
	void		HandleTouchEvent(GLint x, GLint y, bool bIsPresseded);
	void		Exit();

	SoLoud::Soloud gSoloud; // SoLoud engine
	SoLoud::Wav gWave;      // One wave file
	SavingSys SaveFile;
private:
	

};


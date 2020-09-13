#pragma once
#include "AnimationSprite2D.h"
#include "Character.h"
#include "Sprite2D.h"

class InteractOBJ : public AnimationSprite2D
{
private:
	int m_mode;// to change to other function// mode 1 = heal, mode 2 = damage;
public:
	InteractOBJ();
	InteractOBJ(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime, int mode);
	int getMode();

	void PlusHeal();
	void PlusDamage();
	void ToWar();
	void DoneMapGSPlay();
	void ToMenu();
	void Init();
	void Draw();
	void Update(GLfloat deltatime, std::shared_ptr<Character>  m_Character, int& interactedMode);

};
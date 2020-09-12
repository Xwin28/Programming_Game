#pragma once
#include "AnimationSprite2D.h"

class VFX : public AnimationSprite2D
{
public:
	VFX();
	VFX(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime); 
	void Init();
	void Draw();
	void Update(GLfloat deltatime);
private:
	float m_time;
	bool m_DoOne;

};
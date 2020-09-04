#pragma once
#include "Sprite2D.h"

class AnimationSprite2D: public Sprite2D
{
public:
	AnimationSprite2D();

	AnimationSprite2D
	(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime);
	void Init() override;
	void Draw() override;
	void Update(GLfloat deltatime) override;
protected:
	int m_numFrame;
	float m_frameTime;
	int m_currentFrame;
	float m_currentTime;
};
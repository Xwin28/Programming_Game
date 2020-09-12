#include "AnimationSprite2D.h"
#include "VFX.h"
#include "ResourceManagers.h"

VFX::VFX(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime)
	:AnimationSprite2D(model, shader, texture, _numFrame, _frameTime)
{
	m_DoOne = false;
	m_time = 0;
}

void VFX::Init() { AnimationSprite2D::Init(); }
void VFX::Draw() { AnimationSprite2D::Draw(); }
void VFX::Update(GLfloat deltatime)
{ 
	
	if (!m_DoOne)
	{
		AnimationSprite2D::Update(deltatime);
		m_time += deltatime;
		if (m_time > 1.3)
		{
			m_pTexture = ResourceManagers::GetInstance()->GetTexture("VFX//Blood_01");
			m_pShader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			SetSize(64, 64);
			m_time = 0;
			m_DoOne = true;
		}
	}

}
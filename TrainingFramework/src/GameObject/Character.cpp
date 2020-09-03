#include "Character.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "AnimationSprite2D.h"




Character::Character():m_Speed(10){}
Character::Character(float _speed):m_Speed(_speed){}
Character::~Character(){}


void Character::Falling()
{}
void Character::Moving()
{}
void Character::ATk()
{}
void Character::Dodge()
{}
void Character::Update()
{}
void Character::Draw()
{
	//shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	//texture = ResourceManagers::GetInstance()->GetTexture("Character//Player//Idle");
	//std::shared_ptr<AnimationSprite2D> Character = std::make_shared<AnimationSprite2D>(model, shader, texture, 8, 0.1f);
	//Character->Set2DPosition(screenWidth / 2, screenHeight / 2);
	//Character->SetSize(200, 200);
	//m_ListAnimation.push_back(Character);
}
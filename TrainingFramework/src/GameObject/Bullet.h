#pragma once

#include "Sprite2D.h"
#include "Character.h"
#include "Enemy.h"
#include "VFX.h"
class Bullet : public Sprite2D
{
private:
	float m_Speed;
	float m_Horizontal;
	bool m_Des;
	bool m_Owner;//true = player, false = enemy
	
public:
	bool m_IsBossOwner;
	Bullet();
	Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float _Speed, float _Horizontal);
	void setHorizontal(float _Horizontal)
	{
		m_Horizontal = _Horizontal;
	}
	bool GetOner();
	bool getDES();
	void Moving(GLfloat deltatime, std::shared_ptr<Character>& _Character, std::vector<std::shared_ptr<Enemy>>& m_ListEnemy, std::vector<std::shared_ptr<Sprite2D>>& _ListVFX);
	
	void Init() ;
	void Draw() ;
	void Update(GLfloat deltatime, std::shared_ptr<Character> &_Character, std::vector<std::shared_ptr<Enemy>>& m_ListEnemy, std::vector<std::shared_ptr<Sprite2D>>& _ListVFX);
	void DestroyOBJ();
};
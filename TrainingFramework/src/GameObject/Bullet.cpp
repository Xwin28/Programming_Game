#include "Bullet.h"
#include "Sprite2D.h"
#include "Character.h"
#include "Enemy.h"
#include "GameManager/ResourceManagers.h"

Bullet::Bullet() :m_Speed(500), m_Horizontal(1) {}
Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, 
	float _Speed, float _Horizontal): m_Speed(_Speed), m_Horizontal(_Horizontal), Sprite2D(model, shader, texture), m_Des(false)
{

	m_Owner = false;
	if (m_Horizontal == -1)// do not run if already turn
	{

		FlipY(-1.0f);
	}
	else if (m_Horizontal == 1)// do not run if already turn
	{
		FlipY(1.0f);
	}
}
void Bullet::Init() { Sprite2D::Init(); }
bool Bullet::GetOner()
{
	return m_Owner;
}
void Bullet::Draw() { Sprite2D::Draw(); }
void Bullet::DestroyOBJ()
{
	m_Des = true;
}
bool Bullet::getDES()
{
	return m_Des;
}
void Bullet::Moving(GLfloat deltatime, std::shared_ptr<Character>& _Character, std::vector<std::shared_ptr<Enemy>>& m_ListEnemy,
	std::vector<std::shared_ptr<Sprite2D>>& _ListVFX)
{

	if (!m_Owner)
	{
		if (abs(Get2DPosition().x - _Character->Get2DPosition().x) < 5
			&& abs(Get2DPosition().y - _Character->Get2DPosition().y) < 20)
		{
			//HIt Player
			_Character->Hurt(500);
			//+++++++++++++++++++++++++
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
			auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
			auto texture = ResourceManagers::GetInstance()->GetTexture("VFX//HITDone");
			std::shared_ptr<VFX> _VFX = std::make_shared<VFX>(model, shader, texture, 8, 0.05);
			_VFX->Set2DPosition(_Character->Get2DPosition().x, _Character->Get2DPosition().y);
			_VFX->SetSize(192, 192);
			_ListVFX.push_back(_VFX);
			//========================
			DestroyOBJ();

		}
		else
			if (Get2DPosition().x > 10 && Get2DPosition().x < 1270)
			{

				if (abs(Get2DPosition().x - _Character->Get2DPosition().x + (_Character->GetHorizontal() * -45)) < 45
					&& abs(Get2DPosition().y - _Character->Get2DPosition().y) < 20)
				{
					//Player Block Bullet
					if (_Character->GetATK() && _Character->GetnBlock() > 0)
					{
						m_Horizontal = m_Horizontal * -1;
						m_Owner = true;
					}
				}



				Set2DPosition(Get2DPosition().x + m_Speed * m_Horizontal * deltatime, Get2DPosition().y);

			}
			else
			{
				DestroyOBJ();
			}
	}
	else if (m_Owner)// Bullet Of Player
	{


		if (abs(Get2DPosition().x - _Character->Get2DPosition().x) < 5
			&& abs(Get2DPosition().y - _Character->Get2DPosition().y) < 20)
		{
			//HIt Player
			//_Character->Hurt(500);

			DestroyOBJ();

		}
		else
			if (Get2DPosition().x > 10 && Get2DPosition().x < 1270)
			{

				std::vector<int> _ListIndex;
				_ListIndex.clear();
				int _IndexInListE = 0;
				for (auto obj : m_ListEnemy)
				{

					if (abs(Get2DPosition().x - obj->Get2DPosition().x) < 5
						&& abs(Get2DPosition().y - obj->Get2DPosition().y) < 20)
					{
						if (obj->GetTypeEnemy() != 4)
						{
							_ListIndex.push_back(_IndexInListE);
						}
						//m_ListEnemy.erase(m_ListEnemy.begin());


					}
					_IndexInListE++;
				}

				for (auto obj_index : _ListIndex)
				{
					_IndexInListE = 0;
					for (auto obj_E : m_ListEnemy)
					{
						if (_IndexInListE == obj_index)
						{
							m_ListEnemy.erase(m_ListEnemy.begin() + _IndexInListE);
							//+++++++++++++++++++++++++
							auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
							auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
							auto texture = ResourceManagers::GetInstance()->GetTexture("VFX//HITDone");
							std::shared_ptr<VFX> _VFX = std::make_shared<VFX>(model, shader, texture, 8, 0.05);
							_VFX->Set2DPosition(obj_E->Get2DPosition().x, obj_E->Get2DPosition().y);
							_VFX->SetSize(192, 192);
							_ListVFX.push_back(_VFX);
							//========================
							DestroyOBJ();

						}
						_IndexInListE++;
					}

				}
				



				Set2DPosition(Get2DPosition().x + m_Speed * m_Horizontal * deltatime, Get2DPosition().y);

			}
			else
			{
				DestroyOBJ();
			}











		
		
	}

	


}
void Bullet::Update(GLfloat deltatime, std::shared_ptr<Character> &_Character, std::vector<std::shared_ptr<Enemy>>& m_ListEnemy, std::vector<std::shared_ptr<Sprite2D>>& _ListVFX)
{
	Moving(deltatime, _Character, m_ListEnemy, _ListVFX);
}
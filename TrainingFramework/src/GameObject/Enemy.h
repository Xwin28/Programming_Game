#pragma once
#include <string>
#include "Sprite2D.h"
#include "AnimationSprite2D.h"


class Enemy : public AnimationSprite2D
{
private:

	float m_Speed;
	float m_heal;
	float m_jumpHeight;
	float m_coin;
	int m_numberDodge;
	int m_numBlock;

	bool m_isJump;//Check Jump
	bool m_onGround;//Check Falling
	bool m_Atk;//Check ATk
	bool m_CanATK;
	float _yPos;
	float _xPos;
	float m_horizotal;
	float _newPos;//move to new pos
	std::string m_animNow;
	int m_TypeEnemy;//1=Normal, 2=Melle, 3=Range, 4=Boss
	//Animation
	std::shared_ptr<Texture>	m_animIdle, m_animIRun, m_animIFall, m_animIJump, m_animIATK, m_animIDeath, m_animIDodge, m_animIShield, m_animIStayDeath;

	int m_nIdle, m_nRun, m_nFall, m_nDeath, m_nAtk, m_nShield, m_nStayDeath;
	bool doOne;
	float m_time;
	float m_timeATK;
	float m_timeWaitATK;
public:

	Enemy();

	Enemy(float _speed, float _heal, int _numDodge, int _numBlock, float m_jumpHeight,
		std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _frameTime,
		std::shared_ptr<Texture> _Idle, std::shared_ptr<Texture> _Run, std::shared_ptr<Texture> Fall, std::shared_ptr<Texture> _Death, std::shared_ptr<Texture> _ATK,
		std::shared_ptr<Texture> _Shield, std::shared_ptr<Texture> _StayDead
		,int _nIdle, int _nRun, int _nFall, int _nDeath, int _nAtk,int _nShield, int _nStayDeath,  int _TypeEnemy
	);
	~Enemy();
	int GetTypeEnemy();
	float GetHorizontal();
	void SetTexture(std::string _mode);

	void Dead(Vector2 _PosCharacter, int damage);

	void Init();
	void Update(GLfloat deltatime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock);
	void Draw();

	void Falling(float _deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock);
	void Moving(float _horizontal, GLfloat deltatime);
	bool ATk(Vector2 _PosCharacter, Vector2 _SizeCharacter);
	bool Shoot();
	void Dodge();
	void Jump();
	

	float RandomFloat(float min, float max);
	int Randomint(int min, int max);
	//AI
	void AiNormal(GLfloat deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock);
	void AiNormal_Melle(GLfloat deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock, Vector2 _PosCharacter, Vector2 _SizeCharacter, bool & _HitPlayer);
	void AiNormal_Range(GLfloat deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock, Vector2 _PosCharacter, Vector2 _SizeCharacter, bool& _HitPlayer);
	void AiBoss(GLfloat deltaTime, std::vector<std::shared_ptr<Sprite2D>> m_ListBlock, Vector2 _PosCharacter, Vector2 _SizeCharacter, bool& _HitPlayer, bool& _SpawnEnemy);
};
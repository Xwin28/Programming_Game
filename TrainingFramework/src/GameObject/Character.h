#pragma once
class Character
{
private:
	float m_Speed;
public:
	Character();
	Character(float _speed);
	~Character();

	void Falling();
	void Moving();
	void ATk();
	void Dodge();
	void Update();
	void Draw();
};
#pragma once

class Vector2;

class Vector2F
{
public:
	//�����o�֐�
	Vector2F(void); //�f�t�H���g�R���X�g���N�^
	Vector2F(float,float);	//�R���X�g���N�^
	Vector2F(Vector2);		//�R���X�g���N�^
	~Vector2F(void);	//�f�X�g���N�^

	Vector2 ToVector2(void);//Vector2�ւ̕ϊ�

	//�ϐ�
	float x_;
	float y_;
};
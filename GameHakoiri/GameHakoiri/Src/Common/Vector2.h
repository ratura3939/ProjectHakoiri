#pragma once

class Vector2F;

class Vector2
{
public:
	//�����o�֐�
	Vector2(void);	//�R���X�g���N�^
	Vector2(int, int);
	~Vector2(void);	//�f�X�g���N�^

	Vector2F ToVector2F(void);	//Vector2F�ւ̕ϊ�

	//�ϐ�
	int x_;
	int y_;
};
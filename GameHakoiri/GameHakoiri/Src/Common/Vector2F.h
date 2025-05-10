#pragma once

class Vector2;

class Vector2F
{
public:

	//�萔
	float VECTOR2F_ZERO = 0.0f ;

	//�����o�֐�
	Vector2F(void); //�f�t�H���g�R���X�g���N�^
	Vector2F(float, float);	//�R���X�g���N�^
	Vector2F(Vector2);		//�R���X�g���N�^
	~Vector2F(void);	//�f�X�g���N�^

	Vector2 ToVector2(void);//Vector2�ւ̕ϊ�

	Vector2F operator+(const Vector2F& vec)const { return { x + vec.x,y + vec.y }; }
	Vector2F operator-(const Vector2F& vec)const { return { x - vec.x,y - vec.y }; }
	Vector2F operator*(const Vector2F& vec)const { return { x * vec.x,y * vec.y }; }
	Vector2F operator/(const Vector2F& vec)const { return { x / vec.x,y / vec.y }; }
	void operator+=(const Vector2F& vec)
	{
		x += vec.x;
		y += vec.y;
	}
	void operator-=(const Vector2F& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}
	void operator*=(const Vector2F& vec)
	{
		x *= vec.x;
		y *= vec.y;
	}
	void operator/=(const Vector2F& vec)
	{
		x /= vec.x;
		y /= vec.y;
	}
	//�ϐ�
	float x;
	float y;
};

//struct Position
//{
//	//�ϐ�
//	float x;
//	float y;
//
//	Position operator+(const Position& vec)const { return { x + vec.x,y + vec.y }; }
//	Position operator-(const Position& vec)const { return { x - vec.x,y - vec.y }; }
//	Position operator*(const Position& vec)const { return { x * vec.x,y * vec.y }; }
//	Position operator/(const Position& vec)const { return { x / vec.x,y / vec.y }; }
//	void operator+=(const Position& vec)
//	{
//		x += vec.x;
//		y += vec.y;
//	}
//	void operator-=(const Position& vec)
//	{
//		x -= vec.x;
//		y -= vec.y;
//	}
//	void operator*=(const Position& vec)
//	{
//		x *= vec.x;
//		y *= vec.y;
//	}
//	void operator/=(const Position& vec)
//	{
//		x /= vec.x;
//		y /= vec.y;
//	}
//
//	Vector2I ToVector2I(void);
//};

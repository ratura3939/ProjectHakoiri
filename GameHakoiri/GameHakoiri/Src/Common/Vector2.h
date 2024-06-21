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

	Vector2 operator+(const Vector2& vec)const { return { x + vec.x,y + vec.y }; }
	Vector2 operator-(const Vector2& vec)const { return { x - vec.x,y - vec.y }; }
	Vector2 operator*(const Vector2& vec)const { return { x * vec.x,y * vec.y }; }
	Vector2 operator/(const Vector2& vec)const { return { x / vec.x,y / vec.y }; }
	void operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
	}
	void operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}
	void operator*=(const Vector2& vec)
	{
		x *= vec.x;
		y *= vec.y;
	}
	void operator/=(const Vector2& vec)
	{
		x /= vec.x;
		y /= vec.y;
	}

	//�ϐ�
	int x;
	int y;
};

//struct Vector2I
//{
//	//�ϐ�
//	int x;
//	int y;
//
//
//	Vector2I operator+(const Vector2I& vec)const { return { x + vec.x,y + vec.y }; }
//	Vector2I operator-(const Vector2I& vec)const { return { x - vec.x,y - vec.y }; }
//	Vector2I operator*(const Vector2I& vec)const { return { x * vec.x,y * vec.y }; }
//	Vector2I operator/(const Vector2I& vec)const { return { x / vec.x,y / vec.y }; }
//	void operator+=(const Vector2I& vec)
//	{
//		x += vec.x;
//		y += vec.y;
//	}
//	void operator-=(const Vector2I& vec)
//	{
//		x -= vec.x;
//		y -= vec.y;
//	}
//	void operator*=(const Vector2I& vec)
//	{
//		x *= vec.x;
//		y *= vec.y;
//	}
//	void operator/=(const Vector2I& vec)
//	{
//		x /= vec.x;
//		y /= vec.y;
//	}
//
//	Position ToPosition(void);
//};
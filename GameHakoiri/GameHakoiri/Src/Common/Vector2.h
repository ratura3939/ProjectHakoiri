#pragma once

class Vector2F;

class Vector2
{
public:
	//メンバ関数
	Vector2(void);	//コンストラクタ
	Vector2(int, int);
	~Vector2(void);	//デストラクタ

	Vector2F ToVector2F(void);	//Vector2Fへの変換

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

	//変数
	int x;
	int y;
};

//struct Vector2I
//{
//	//変数
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
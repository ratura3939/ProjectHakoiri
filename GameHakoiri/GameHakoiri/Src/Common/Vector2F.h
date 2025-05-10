#pragma once

class Vector2;

class Vector2F
{
public:

	//定数
	float VECTOR2F_ZERO = 0.0f ;

	//メンバ関数
	Vector2F(void); //デフォルトコンストラクタ
	Vector2F(float, float);	//コンストラクタ
	Vector2F(Vector2);		//コンストラクタ
	~Vector2F(void);	//デストラクタ

	Vector2 ToVector2(void);//Vector2への変換

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
	//変数
	float x;
	float y;
};

//struct Position
//{
//	//変数
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

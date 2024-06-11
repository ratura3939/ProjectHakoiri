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

	Vector2 operator+(const Vector2& vec)const { return { x_ + vec.x_,y_ + vec.y_ }; }
	Vector2 operator-(const Vector2& vec)const { return { x_ - vec.x_,y_ - vec.y_ }; }
	Vector2 operator*(const Vector2& vec)const { return { x_ * vec.x_,y_ * vec.y_ }; }
	Vector2 operator/(const Vector2& vec)const { return { x_ / vec.x_,y_ / vec.y_ }; }
	void operator+=(const Vector2& vec)
	{
		x_ += vec.x_;
		y_ += vec.y_;
	}
	void operator-=(const Vector2& vec)
	{
		x_ -= vec.x_;
		y_ -= vec.y_;
	}
	void operator*=(const Vector2& vec)
	{
		x_ *= vec.x_;
		y_ *= vec.y_;
	}
	void operator/=(const Vector2& vec)
	{
		x_ /= vec.x_;
		y_ /= vec.y_;
	}

	//変数
	int x_;
	int y_;
};
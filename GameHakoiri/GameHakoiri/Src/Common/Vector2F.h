#pragma once

class Vector2;

class Vector2F
{
public:
	//メンバ関数
	Vector2F(void); //デフォルトコンストラクタ
	Vector2F(float,float);	//コンストラクタ
	Vector2F(Vector2);		//コンストラクタ
	~Vector2F(void);	//デストラクタ

	Vector2 ToVector2(void);//Vector2への変換

	//変数
	float x_;
	float y_;
};
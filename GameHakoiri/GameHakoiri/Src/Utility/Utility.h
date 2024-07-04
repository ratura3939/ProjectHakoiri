#pragma once
#include<string>
#include<vector>
#include"../Common/Vector2.h"
#include"../Common/Vector2F.h"

#include <DxLib.h>

class Utility
{
public:

	// ラジアン(rad)・度(deg)変換用
	static constexpr float RAD2DEG = (180.0f / DX_PI_F);
	static constexpr float DEG2RAD = (DX_PI_F / 180.0f);

	static constexpr VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };
	static constexpr VECTOR VECTOR_ONE = { 1.0f, 1.0f, 1.0f };

	//列挙型
	//************************************************************
	//方向
	enum class DIR
	{
		UP
		,RIGHT
		,DOWN
		,LEFT
		,MAX
	};

	//文字列の分割
	static std::vector<std::string> Split(std::string& line, char delimiter);	//delimiliterは「区切り記号」の意

	//四捨五入
	static int Round(float);
	static Vector2 Round(Vector2F);


	//ベクトルの長さ取得
	static double Distance(const Vector2& v1, const Vector2& v2);


	// ラジアン(rad)から度(deg)
	static double Rad2DegD(double rad);
	static float Rad2DegF(float rad);
	static int Rad2DegI(int rad);

	// 度(deg)からラジアン(rad)
	static double Deg2RadD(double deg);
	static float Deg2RadF(float deg);
	static int Deg2RadI(int deg);

	// 0～360度の範囲に収める
	static double DegIn360(double deg);

	// 0(0)～2π(360度)の範囲に収める
	static double RadIn2PI(double rad);

	static float GetInnerProductF(Vector2F v1, Vector2F v2);
	static float GetCrossProductF(Vector2F v1, Vector2F v2);
};
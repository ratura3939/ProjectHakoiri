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
};
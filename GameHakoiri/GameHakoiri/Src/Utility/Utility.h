#pragma once
#include<string>
#include<vector>
#include"../Common/Vector2.h"
#include"../Common/Vector2F.h"

class Utility
{
public:
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
};
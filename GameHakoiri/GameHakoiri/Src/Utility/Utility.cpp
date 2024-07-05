#include<DxLib.h>
#include<sstream>
#include"Utility.h"

//文字列の分割
//********************************************************
std::vector<std::string> Utility::Split(std::string& line, char delimiter)
{
	//動的配列の返り値を準備
	std::vector<std::string> result;

	//文字配列操作用のクラスに置き換える
	std::istringstream stream(line);

	std::string filed;

	//streamを順に読み込み
	//3個目の引数で指定された文字までを二個目の引数に返す
	while (getline(stream, filed, delimiter))
	{
		//配列に追加
		result.push_back(filed);
	}
	return result;
}

//四捨五入
int Utility::Round(float value)
{
	return static_cast<int>(round(value));
}
Vector2 Utility::Round(Vector2F value)	//float型のVector2Fをint型のVector2に四捨五入し直す。
{
	Vector2 ret;

	ret.x = static_cast<int>(roundf(value.x));
	ret.y = static_cast<int>(roundf(value.y));

	return ret;
}

double Utility::Distance(const Vector2& v1, const Vector2& v2)
{
	return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}

double Utility::Rad2DegD(double rad)
{
	return rad * (180.0 / DX_PI);
}

float Utility::Rad2DegF(float rad)
{
	return rad * (180.0f / DX_PI_F);
}

int Utility::Rad2DegI(int rad)
{
	return rad * Round(180.0f / DX_PI_F);
}

double Utility::Deg2RadD(double deg)
{
	return deg * (DX_PI / 180.0);
}

float Utility::Deg2RadF(float deg)
{
	return deg * (DX_PI_F / 180.0f);
}

int Utility::Deg2RadI(int deg)
{
	return deg * Round(DX_PI_F / 180.0f);
}

double Utility::DegIn360(double deg)
{
	deg = fmod(deg, 360.0);
	if (deg < 0.0f)
	{
		deg += 360.0;
	}
	return deg;
}

double Utility::RadIn2PI(double rad)
{
	rad = fmod(rad, DX_TWO_PI);
	if (rad < 0.0)
	{
		rad += DX_TWO_PI;
	}
	return rad;
}

float Utility::GetInnerProductF(Vector2F v1, Vector2F v2)
{
	return (v1.x * v2.x) + (-v1.y * -v2.y);
}

float Utility::GetCrossProductF(Vector2F v1, Vector2F v2)
{
	return (v1.x * v2.y) - (v1.y * v2.x);
}

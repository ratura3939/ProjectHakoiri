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

	ret.x_ = static_cast<int>(roundf(value.x_));
	ret.y_ = static_cast<int>(roundf(value.y_));

	return ret;
}
#include"Vector2.h"
#include"Vector2F.h"

//コンストラクタ
Vector2::Vector2(void)
{
	x = 0;
	y = 0;
}
Vector2::Vector2(int x_, int y_)
{
	x = x_;
	y = y_;
}
//デストラクタ
Vector2::~Vector2(void)
{

}

//Vector2Fへの変換
Vector2F Vector2::ToVector2F(void)
{
	Vector2F ret;
	ret.x = static_cast<float>(x);
	ret.y = static_cast<float>(y);
	return ret;
}

//Vector2F Vector2::ToVector2F(void)
//{
//	Vector2F ret;
//	ret.x = static_cast<float>(x);
//	ret.y = static_cast<float>(y);
//	return ret;
//}//Vector2Fへの変換

#include"Vector2.h"
#include"Vector2F.h"

//コンストラクタ
Vector2::Vector2(void)
{
	x_ = 0;
	y_ = 0;
}
Vector2::Vector2(int x, int y)
{
	x_ = x;
	y_ = y;
}
//デストラクタ
Vector2::~Vector2(void)
{

}

//Vector2Fへの変換
Position Vector2::ToVector2F(void)
{
	Position ret;
	ret.x_ = static_cast<float>(x_);
	ret.y_ = static_cast<float>(y_);
	return ret;
}
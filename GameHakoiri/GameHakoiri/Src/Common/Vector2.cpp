#include"Vector2.h"
#include"Vector2F.h"

//�R���X�g���N�^
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
//�f�X�g���N�^
Vector2::~Vector2(void)
{

}

//Vector2F�ւ̕ϊ�
Position Vector2::ToVector2F(void)
{
	Position ret;
	ret.x_ = static_cast<float>(x_);
	ret.y_ = static_cast<float>(y_);
	return ret;
}
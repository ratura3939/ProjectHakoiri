#include<tgmath.h>
#include"Vector2F.h"
#include"Vector2.h"

//�R���X�g���N�^
Vector2F::Vector2F(void)
{
	x_ = 0.0f;
	y_ = 0.0f;
}

//�R���X�g���N�^
Vector2F::Vector2F(float x,float y)
{
	x_ = x;
	y_ = y;
}
Vector2F::Vector2F(Vector2)
{
}
//�f�X�g���N�^
Vector2F::~Vector2F(void)
{

}
//Vector2�ւ̕ϊ�
Vector2 Vector2F::ToVector2(void)
{
	Vector2 ret;

	ret.x_ = static_cast<int>(roundf(x_));
	ret.y_ = static_cast<int>(roundf(y_));

	return ret;
}
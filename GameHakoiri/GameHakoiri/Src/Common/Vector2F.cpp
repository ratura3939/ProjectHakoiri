#include<tgmath.h>
#include"Vector2F.h"
#include"Vector2.h"

//�R���X�g���N�^
Vector2F::Vector2F(void)
{
	x = 0.0f;
	y = 0.0f;
}

//�R���X�g���N�^
Vector2F::Vector2F(float x_, float y_)
{
	x = x_;
	y = y_;
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

	ret.x = static_cast<int>(roundf(x));
	ret.y = static_cast<int>(roundf(y));

	return ret;
}
//Vector2 Vector2F::ToVector2(void)
//{
//	Vector2 ret;
//
//	ret.x = static_cast<int>(roundf(x));
//	ret.y = static_cast<int>(roundf(y));
//
//	return ret;
//}//Vector2�ւ̕ϊ�

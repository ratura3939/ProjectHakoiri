#include"Vector2.h"
#include"Vector2F.h"

//�R���X�g���N�^
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
//�f�X�g���N�^
Vector2::~Vector2(void)
{

}

//Vector2F�ւ̕ϊ�
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
//}//Vector2F�ւ̕ϊ�

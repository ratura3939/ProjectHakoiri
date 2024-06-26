#include<DxLib.h>
#include<sstream>
#include"Utility.h"

//������̕���
//********************************************************
std::vector<std::string> Utility::Split(std::string& line, char delimiter)
{
	//���I�z��̕Ԃ�l������
	std::vector<std::string> result;

	//�����z�񑀍�p�̃N���X�ɒu��������
	std::istringstream stream(line);

	std::string filed;

	//stream�����ɓǂݍ���
	//3�ڂ̈����Ŏw�肳�ꂽ�����܂ł��ڂ̈����ɕԂ�
	while (getline(stream, filed, delimiter))
	{
		//�z��ɒǉ�
		result.push_back(filed);
	}
	return result;
}

//�l�̌ܓ�
int Utility::Round(float value)
{
	return static_cast<int>(round(value));
}
Vector2 Utility::Round(Vector2F value)	//float�^��Vector2F��int�^��Vector2�Ɏl�̌ܓ��������B
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

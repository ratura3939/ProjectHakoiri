#pragma once
#include<string>
#include<vector>
#include"../Common/Vector2.h"
#include"../Common/Vector2F.h"

#include <DxLib.h>

class Utility
{
public:

	// ���W�A��(rad)�E�x(deg)�ϊ��p
	static constexpr float RAD2DEG = (180.0f / DX_PI_F);
	static constexpr float DEG2RAD = (DX_PI_F / 180.0f);

	static constexpr VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };
	static constexpr VECTOR VECTOR_ONE = { 1.0f, 1.0f, 1.0f };

	//�񋓌^
	//************************************************************
	//����
	enum class DIR
	{
		UP
		,RIGHT
		,DOWN
		,LEFT
		,MAX
	};

	//������̕���
	static std::vector<std::string> Split(std::string& line, char delimiter);	//delimiliter�́u��؂�L���v�̈�

	//�l�̌ܓ�
	static int Round(float);
	static Vector2 Round(Vector2F);


	//�x�N�g���̒����擾
	static double Distance(const Vector2& v1, const Vector2& v2);


	// ���W�A��(rad)����x(deg)
	static double Rad2DegD(double rad);
	static float Rad2DegF(float rad);
	static int Rad2DegI(int rad);

	// �x(deg)���烉�W�A��(rad)
	static double Deg2RadD(double deg);
	static float Deg2RadF(float deg);
	static int Deg2RadI(int deg);

	// 0�`360�x�͈̔͂Ɏ��߂�
	static double DegIn360(double deg);

	// 0(0)�`2��(360�x)�͈̔͂Ɏ��߂�
	static double RadIn2PI(double rad);

	static float GetInnerProductF(Vector2F v1, Vector2F v2);
	static float GetCrossProductF(Vector2F v1, Vector2F v2);
};
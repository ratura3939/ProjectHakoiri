#pragma once
#include<string>
#include<vector>
#include"../Common/Vector2.h"
#include"../Common/Vector2F.h"

class Utility
{
public:
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
};
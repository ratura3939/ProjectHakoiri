//#pragma once
#include"RoomBase.h"

class Wasitu :public RoomBase
{
public:
	//�萔
	static constexpr int PAZZLE_SIZE_X = 1;
	static constexpr int PAZZLE_SIZE_Y = 1;
	static constexpr int STEALTH_SIZE_Y = 30;
	static constexpr int STEALTH_SIZE_Y = 30;

	void SetParam(void) override; //�p�����[�^�̐ݒ�
};
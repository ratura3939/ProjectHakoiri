#pragma once
#include"RoomBase.h"

class Wasitu :public RoomBase
{
public:
	Wasitu(int roomImg);
	~Wasitu(void);

	void SetParam(void) override; //�p�����[�^�̐ݒ�
};
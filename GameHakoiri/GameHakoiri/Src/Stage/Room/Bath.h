#pragma once
#include "RoomBase.h"
class Bath :public RoomBase
{
public:
	Bath(int roomImg);
	~Bath(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�
};


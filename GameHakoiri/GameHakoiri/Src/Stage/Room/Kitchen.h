#pragma once
#include "RoomBase.h"
class Kitchen :public RoomBase
{
public:
	Kitchen(int roomImg);
	~Kitchen(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�
};


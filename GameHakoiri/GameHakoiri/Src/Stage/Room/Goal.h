#pragma once
#include "RoomBase.h"
class Goal :public RoomBase
{
public:
	Goal(int roomImg);
	~Goal(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�
};


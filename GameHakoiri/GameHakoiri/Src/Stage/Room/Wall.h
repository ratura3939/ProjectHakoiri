#pragma once
#include "RoomBase.h"
class Wall :public RoomBase
{
public:
	Wall(int roomImg);
	~Wall(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�
};


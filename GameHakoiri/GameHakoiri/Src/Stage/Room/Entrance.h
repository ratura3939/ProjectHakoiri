#pragma once
#include "RoomBase.h"
class Entrance :public RoomBase
{
public:
	Entrance(int roomImg);
	~Entrance(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�

};


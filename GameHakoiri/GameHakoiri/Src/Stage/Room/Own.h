#pragma once
#include "RoomBase.h"
class Own :public RoomBase
{
public:
	Own(int roomImg, int sizeX, int sizeY);
	~Own(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�

};


#pragma once
#include "RoomBase.h"
class Living :public RoomBase
{
public:
	Living(int roomImg, int sizeX, int sizeY);
	~Living(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�
};

